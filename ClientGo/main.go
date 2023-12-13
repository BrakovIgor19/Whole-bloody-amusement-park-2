package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/widget"
	"log"
	"regexp"
	"sync"
	"time"
)

const (
	PROCESS_CLIENT = iota
	CLOSE_CLIENT
	UPDATE_USER_LIST
	UPDATE_MESSAGE
	SENT_MASSAGE
)

func main() {
	// Запускаем окно
	myApp := app.New()
	win := myApp.NewWindow("vk1000-7")
	win.Resize(fyne.Size{600, 400})
	var authorizationForm = NewAuthorizationForm()
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

	var ch = make(chan int, 2)
	var ch2 = make(chan int, 1)
	var ch3 = make(chan string, 1)
	//var ch3 = make(chan int, 1)
	var wg sync.WaitGroup
	var wg2 sync.WaitGroup
	//var wg3 sync.WaitGroup
	var wg4 sync.WaitGroup
	wg4.Add(01)
	//wg3.Add(1)
	wg2.Add(2)
	wg.Add(1)
	authorizationForm.EnterButton.OnTapped = func() {
		matched, _ := regexp.MatchString(`^[-\w.]+@([A-Za-z0-9][-A-Za-z0-9]+\.)+[A-Za-z]{2,4}$`, authorizationForm.EmailEntry.Text)
		if matched && authorizationForm.PasswordEntry.Text != "" {
			ch2 <- PROCESS_CLIENT
		}
	}

	chatForm.ExitButton.OnTapped = func() {
		ch2 <- CLOSE_CLIENT
	}
	chatForm.SendButton.OnTapped = func() {
		ch2 <- SENT_MASSAGE
	}
	var onClose bool = false
	var wgClose sync.WaitGroup
	wgClose.Add(1)
	win.SetOnClosed(func() {
		onClose = true
		ch2 <- CLOSE_CLIENT
		wgClose.Wait()

	})
	win.SetContent(authorizationForm.Content)
	go func() {
		defer wgClose.Done()
		for range time.Tick(time.Second) {
			if onClose {
				break
			}
			select {
			case task := <-ch2:
				switch task {
				case PROCESS_CLIENT:
					client = NewClient()
					go client.Process(ch, ch2, ch3, &wg, &wg2, &chatForm, &authorizationForm)
					ch <- ET_AUTHORIZATION
					client.wg.Done()
					wg.Wait()
					wg.Add(1)
					if <-ch != ET_FAILED_AUTHORIZATION {
						chatForm.FirtsNameLabel.Text = client.FirstName
						chatForm.LastNameLabel.Text = client.LastName
						img, err := fyne.LoadResourceFromPath("../../../Resource/Avatars/" + client.NameAvatar)
						if err != nil {
							log.Println("фото не открылась")
						} else {
							chatForm.AvaImage = canvas.NewImageFromResource(img)
						}

						win.SetContent(chatForm.Content)
						//chatForm.AvaImage.Refresh()
						//ch3 <- ET_AUTHORIZATION
						//wg4.Done()
					} else {
						authorizationForm.PasswordEntry.Text = ""
						authorizationForm.PasswordEntry.SetPlaceHolder("Неверная почта или пароль")
					}
				case CLOSE_CLIENT:
					ch <- ET_EXIT
					client.wg.Done()
					wg.Wait()
					wg.Add(1)
					authorizationForm.PasswordEntry.Text = ""
					authorizationForm.EmailEntry.Text = ""
					win.SetContent(authorizationForm.Content)

				case UPDATE_USER_LIST:
					var bufStrs []string
					for key := range client.SelectItemToIdConv {
						bufStrs = append(bufStrs, client.CacheConversations[client.SelectItemToIdConv[key]])
					}
					chatForm.ListData.Set(bufStrs)

				case UPDATE_MESSAGE:
					idConv := <-ch
					//if _, ok := client.SelectItemToIdConv[uint(selectedItem)]; ok {
					if selectedItem != -1 && idConv == int(client.SelectItemToIdConv[uint(selectedItem)]) {
						chatForm.WinChatEntry.Append(client.History[uint(idConv)][len(client.History[uint(idConv)])-1] + "\n")
					}
					//}
				case SENT_MASSAGE:
					if selectedItem != -1 {
						ch <- ET_SEND_MESSAGE
						ch <- int(client.SelectItemToIdConv[uint(selectedItem)])
						ch3 <- chatForm.InputMessageEntry.Text
						client.wg.Done()
						wg.Wait()
						wg.Add(1)
						//idConv := int(client.SelectItemToIdConv[uint(selectedItem)])
						chatForm.WinChatEntry.Append(client.FirstName + " " + client.LastName + ": " + chatForm.InputMessageEntry.Text + "\n")
						chatForm.InputMessageEntry.SetText("")
					}
				}

			default:
				//time.Sleep(100 * time.Millisecond) // Ждем, чтобы не блокировать процессор
			}
		}
	}()
	/*go func() {
		for range time.Tick(time.Second) {
			win.SetContent(chatForm.Content)
		}
	}()*/
	win.ShowAndRun()

}

func showChat(win fyne.Window) {

	//win.SetContent(chatContent)
}

func isValidCredentials(email, password string) bool {
	// Реализуйте свою логику проверки учетных данных
	return email == "user@example.com" && password == "password"
}
