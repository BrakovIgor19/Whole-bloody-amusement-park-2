#include "pch.h"
#include "ConsoleFormatOutIn.h"

string ConsoleFormatOutIn::ReadStringWithoutMovingCursor()
{
	short bufX, bufY;
	string str;
	bufX = Console::getXcoord(); bufY = Console::getYcoord();
	getline(cin, str);
	Console::gotoxy(bufX, bufY);
	return str;
}

void ConsoleFormatOutIn::WriteTextCenterThisCoord(short x, short y, const string& text)
{
	Console::gotoxy(x - (text.size() / 2), y);
	cout << text;
}

void ConsoleFormatOutIn::OutputVectorStringColumnAlignedRight(short left, short top, const vector <string>& vectorStr, const vector <string>& vectorDate)
{


	// Íàéäåì ñòðîêó ìàêñèìàëüíî äëèíû
	int maxLength = AuxiliaryFunctions::FindMaxLengthVectorStr(vectorStr);

	// Âûâîäèì ìàññèâ ñòðîê
	for (int i = 0; i < vectorStr.size(); ++i)
	{
		// Ïåðåõîäèì Ïåðåõîäèì íà íîâóþ ñòðîêó è âûâîäèì 
		Console::gotoxy(left, top + i);
		cout << setw(maxLength) << vectorStr[i] << " " << vectorDate[i];
	}
}

void ConsoleFormatOutIn::PaintTextBackground(short x, short y, const string& str, ConsoleColor text, ConsoleColor background)
{
	HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	GetConsoleScreenBufferInfo(descriptor, &screenBuffer);
	Console::gotoxy(x, y);
	Console::SetColor(text, background);
	cout << str;
	Console::gotoxy(x, y);
	SetConsoleTextAttribute(descriptor, screenBuffer.wAttributes);
}