package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
	"log"
	"regexp"
	"sync"
	"time"
)

// Сигналы для главного потока, для обновления формочки
const (
	PROCESS_CLIENT = iota
	CLOSE_CLIENT
	UPDATE_USER_LIST
	UPDATE_MESSAGE
	SEND_MESSAGE
)

func main() {
	// Запускаем окно
	myApp := app.New()
	win := myApp.NewWindow("vk1000-7")
	win.Resize(fyne.Size{600, 400})
	var authorizationForm = NewAuthorizationForm()

	// Форма чата
	var chatForm = NewChatForm()
	var client Client
	var selectedItem int = -1
	chatForm.ConversationsList.OnSelected = func(id widget.ListItemID) {
		selectedItem = id
		chatForm.WinChatEntry.SetText("")
		for _, value := range client.History[client.SelectItemToIdConv[uint(selectedItem)]] {
			chatForm.WinChatEntry.Append(value + "\n")
		}
	}

	var chClient_MainThread = make(chan any)
	var chEventToMainThread = make(chan int, 10)

	authorizationForm.EnterButton.OnTapped = func() {
		matched, _ := regexp.MatchString(`^[-\w.]+@([A-Za-z0-9][-A-Za-z0-9]+\.)+[A-Za-z]{2,4}$`, authorizationForm.EmailEntry.Text)
		if matched && authorizationForm.PasswordEntry.Text != "" {
			chEventToMainThread <- PROCESS_CLIENT
		}
	}

	chatForm.ExitButton.OnTapped = func() {
		chEventToMainThread <- CLOSE_CLIENT
	}
	chatForm.SendButton.OnTapped = func() {
		chEventToMainThread <- SEND_MESSAGE
	}

	var onClose bool = false
	var wgCloseApp sync.WaitGroup
	wgCloseApp.Add(1)
	win.SetOnClosed(func() {
		onClose = true
		chEventToMainThread <- CLOSE_CLIENT
		wgCloseApp.Wait()

	})

	win.SetContent(authorizationForm.Content)

	go func() {
		defer wgCloseApp.Done()

		for range time.Tick(300 * time.Millisecond) {

			if onClose {
				break
			}
			select {

			case task := <-chEventToMainThread:
				switch task {

				case PROCESS_CLIENT:
					client = NewClient()
					go client.Process(chClient_MainThread, chEventToMainThread)
					chClient_MainThread <- ET_AUTHORIZATION
					chClient_MainThread <- authorizationForm.EmailEntry.Text
					chClient_MainThread <- authorizationForm.PasswordEntry.Text

					if (<-chClient_MainThread).(int) == ET_AUTHORIZATION {
						chatForm.FirtsNameLabel.Text = client.FirstName
						chatForm.LastNameLabel.Text = client.LastName
						//img, err := fyne.LoadResourceFromPath("../../../Resource/Avatars/" + client.NameAvatar)
						img, err := fyne.LoadResourceFromPath("C://Users//artem//OneDrive//Рабочий стол//Whole-bloody-amusement-park-2//Resource//Avatars//" + client.NameAvatar)
						if err != nil {
							log.Println("фото не открылась")
						} else {
							chatForm.AvaImage = canvas.NewImageFromResource(img)
						}
						chatForm.Content.RemoveAll()
						chatForm.Content = container.NewAdaptiveGrid(
							3,
							chatForm.FirtsNameLabel,
							chatForm.LastNameLabel,
							chatForm.AvaImage,
							chatForm.WinChatEntry,
							chatForm.InputMessageEntry,
							chatForm.SendButton,
							chatForm.ConversationsList,
							chatForm.ExitButton,
						)

						win.SetContent(chatForm.Content)
					} else {
						authorizationForm.PasswordEntry.Text = ""
						authorizationForm.PasswordEntry.SetPlaceHolder("Неверная почта или пароль")
						chEventToMainThread <- CLOSE_CLIENT
					}

				case CLOSE_CLIENT:
					chClient_MainThread <- ET_EXIT
					<-chClient_MainThread

					authorizationForm.PasswordEntry.SetText("")
					authorizationForm.EmailEntry.SetText("")
					win.SetContent(authorizationForm.Content)

				case UPDATE_USER_LIST:
					var bufStrs []string
					for key := range client.SelectItemToIdConv {
						bufStrs = append(bufStrs, client.CacheConversations[client.SelectItemToIdConv[key]])
					}
					chatForm.ListData.Set(bufStrs)

				case UPDATE_MESSAGE:
					idConv := (<-chClient_MainThread).(uint)
					if selectedItem != -1 && idConv == client.SelectItemToIdConv[selectedItem] {
						chatForm.WinChatEntry.Append(client.History[idConv][len(client.History[idConv])-1] + "\n")
					}

				case SEND_MESSAGE:
					if selectedItem != -1 {
						chClient_MainThread <- ET_SEND_MESSAGE
						chClient_MainThread <- int(client.SelectItemToIdConv[selectedItem])
						chClient_MainThread <- chatForm.InputMessageEntry.Text

						chatForm.WinChatEntry.Append(client.FirstName + " " + client.LastName + ": " + chatForm.InputMessageEntry.Text + "\n")
						chatForm.InputMessageEntry.SetText("")
					}
				}

			default:

			}
		}
	}()

	win.ShowAndRun()

}
