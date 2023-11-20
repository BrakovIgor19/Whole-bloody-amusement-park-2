#include "pch.h"
#include "Console.h"

size_t Console::getXcoord()
{
	GetConsoleScreenBufferInfo(descriptor, &screenBuffer);
	return static_cast<size_t>(screenBuffer.dwCursorPosition.X);
}

size_t Console::getYcoord()
{
	GetConsoleScreenBufferInfo(descriptor, &screenBuffer);
	return static_cast<size_t>(screenBuffer.dwCursorPosition.Y);
}

void Console::gotoxy(size_t x, size_t y)
{
	SetConsoleCursorPosition(descriptor, {static_cast<short>(x), static_cast<short>(y) });
}

void Console::SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(descriptor, (WORD)((background << 4) | text));  
}

void Console::ShowCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorBuffer;
	GetConsoleCursorInfo(descriptor, &cursorBuffer);
	cursorBuffer.bVisible = showFlag; 
	SetConsoleCursorInfo(descriptor, &cursorBuffer);
}

void Console::SetBufferScreenSize(short width, short height)
{
	COORD size = { width, height };
	SetConsoleScreenBufferSize(descriptor, size);
}

void Console::SetCoordWindow(short left, short top, short right, short bottom)
{
	SMALL_RECT coord = { left, top, right, bottom };
	SetConsoleWindowInfo(descriptor, TRUE, &coord);
}

size_t Console::GetWidthWindow()
{
	GetConsoleScreenBufferInfo(descriptor, &screenBuffer);
	return screenBuffer.srWindow.Right - screenBuffer.srWindow.Left;

}

size_t Console::GetHeightWindow()
{
	GetConsoleScreenBufferInfo(descriptor, &screenBuffer);
	return screenBuffer.srWindow.Bottom - screenBuffer.srWindow.Top;
}

void Console::InvertColor()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBuffer);
	WORD fillBeforeInversion = screenBuffer.wAttributes;
	WORD text = (fillBeforeInversion >> 4) & 15;
	WORD background = (fillBeforeInversion << 4) & 240;
	WORD fbI = fillBeforeInversion & 65280;
	SetConsoleTextAttribute(descriptor, (WORD)((text | background) | fbI));
}

void Console::SaveColor()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &forSaveColor);
}

void Console::RestoreÑolor()
{
	SetConsoleTextAttribute(descriptor, forSaveColor.wAttributes);
}




