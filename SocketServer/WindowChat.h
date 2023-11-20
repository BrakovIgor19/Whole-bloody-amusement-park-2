#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "../SocketServer/ConsoleColor.h"
#include "ConsoleFormatOutIn.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class WindowChat
{

public:
	explicit WindowChat(size_t left, size_t top, size_t right, size_t bottom, char frameSymbol);
	explicit WindowChat();
	~WindowChat();
	void Display();
	bool isDisplay() const;
	void Hide();
	string InputMessage();
	void LoadLatestMessages(const vector<string>& str);

private:

	const size_t top;
	const size_t left;
	const size_t right;
	const size_t bottom;
	const size_t height;
	const size_t width;
	const char frameSymbol;
	bool isDisp;

	vector<string> history;
	vector<string> displayedData;
	void DrawData();
	void DrawFrame(size_t width, size_t height);
};


