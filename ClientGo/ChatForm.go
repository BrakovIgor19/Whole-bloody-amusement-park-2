package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/data/binding"
	"fyne.io/fyne/v2/widget"
)

// Создаём контейнеры с контентом под каждую "форму"
// Авторизация

type ChatForm struct {
	FirtsNameLabel    *widget.Label
	LastNameLabel     *widget.Label
	AvaImage          *canvas.Image
	WinChatEntry      *widget.Entry
	InputMessageEntry *widget.Entry
	SendButton        *widget.Button
	ConversationsList *widget.List
	ListData          binding.ExternalStringList
	ExitButton        *widget.Button
	Content           *fyne.Container
}

func NewChatForm() ChatForm {
	var chF ChatForm
	chF.FirtsNameLabel = widget.NewLabel("Имя")

	chF.LastNameLabel = widget.NewLabel("Фамилия")

	img, _ := fyne.LoadResourceFromPath("../../../Resource/Avatars/default.jpg")
	chF.AvaImage = canvas.NewImageFromResource(img)

	chF.WinChatEntry = widget.NewMultiLineEntry()
	chF.WinChatEntry.SetPlaceHolder("Чат")
	chF.WinChatEntry.Disable()

	chF.InputMessageEntry = widget.NewEntry()
	chF.InputMessageEntry.SetPlaceHolder("Введите сообщение")

	chF.SendButton = widget.NewButton("Отправить", nil)
	chF.ListData = binding.BindStringList(&[]string{})
	chF.ConversationsList = widget.NewListWithData(
		chF.ListData,
		func() fyne.CanvasObject {
			return widget.NewLabel("template")
		},
		func(i binding.DataItem, o fyne.CanvasObject) {
			o.(*widget.Label).Bind(i.(binding.String))
		},
	)

	chF.ExitButton = widget.NewButton("Выйти", nil)
	chF.Content = container.NewAdaptiveGrid(
		3,
		chF.FirtsNameLabel,
		chF.LastNameLabel,
		chF.AvaImage,
		chF.WinChatEntry,
		chF.InputMessageEntry,
		chF.SendButton,
		chF.ConversationsList,
		chF.ExitButton,
	)
	return chF
}
