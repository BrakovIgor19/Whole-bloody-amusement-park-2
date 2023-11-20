#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "ConsoleKey.h"
#include <dos.h>
#include "Console.h"

#define ENT -2
#define EXIT -1

using std::string;
using std::vector;
using std::cout;

 class Menu
{

public:
	explicit Menu(const vector<string>& items, size_t top, size_t left);
	explicit Menu(const vector<string>& items);
	~Menu();
	void UpdateItems(const vector<string>& items);
	int ActivateMenu();
	void Hide();
	size_t getActiveItem();
	bool isDisplay() const;

private:
	size_t maxSizeItems;
	size_t activeMenu;
	size_t top;
	size_t left;
	vector<string> items;
	bool isDisp;

	size_t FindMaxSizeItems();
};


