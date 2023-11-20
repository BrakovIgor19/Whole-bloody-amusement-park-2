#pragma once
#include <vector>
#include <iomanip>
#include "AuxiliaryFunctions.h"
#include "../SocketServer/Console.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::setw;

#ifndef ConsoleFormatOutIn_H
#define	ConsoleFormatOutIn_H

struct ConsoleFormatOutIn
{
	static string ReadStringWithoutMovingCursor();
	static void WriteTextCenterThisCoord(short x, short y, const string& text);
	static void OutputVectorStringColumnAlignedRight(short x, short y, const vector <string>& vectorStr, const vector <string>& vectorDate);
	static void PaintTextBackground(short x, short y, const string& str, ConsoleColor text, ConsoleColor background);
};

#endif 
