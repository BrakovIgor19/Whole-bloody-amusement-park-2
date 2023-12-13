package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/data/validation"
	"fyne.io/fyne/v2/widget"
)

// Создаём контейнеры с контентом под каждую "форму"
// Авторизация

type AuthorizationForm struct {
	EmailEntry    *widget.Entry
	PasswordEntry *widget.Entry
	EnterButton   *widget.Button
	Content       *fyne.Container
}

func NewAuthorizationForm() AuthorizationForm {

	var af AuthorizationForm

	af.EmailEntry = widget.NewEntry()
	af.EmailEntry.SetPlaceHolder("Введите почту")
	af.EmailEntry.Validator = validation.NewRegexp(`^[-\w.]+@([A-Za-z0-9][-A-Za-z0-9]+\.)+[A-Za-z]{2,4}$`, "Неверный формат почты!")

	af.PasswordEntry = widget.NewPasswordEntry()
	af.PasswordEntry.SetPlaceHolder("Введите пароль")

	af.EnterButton = widget.NewButton("Войти", nil)

	af.Content = container.NewVBox(
		af.EmailEntry,
		af.PasswordEntry,
		af.EnterButton,
	)
	return af
}
