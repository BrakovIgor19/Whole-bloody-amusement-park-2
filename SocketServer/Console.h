
#include <iostream>
#include <sstream>
#include <Windows.h>
#include "ConsoleColor.h"
#include <clocale>

#ifndef Console_H
#define	Console_H

using std::string;

static struct Console
{
	static void gotoxy(size_t x, size_t y);
	static size_t getXcoord();
	static size_t getYcoord();
	static void SetColor(ConsoleColor text, ConsoleColor background);
	static void ShowCursor(bool showFlag);
	static void SetBufferScreenSize(short width, short height);
	static void SetCoordWindow(short left, short top, short right, short bottom);
	static size_t GetWidthWindow();
	static size_t GetHeightWindow();
	static void InvertColor();
	static void SaveColor();
	static void Restore—olor();
private:
	static inline HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	static inline CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	static inline CONSOLE_SCREEN_BUFFER_INFO forSaveColor;

	
};

#endif

