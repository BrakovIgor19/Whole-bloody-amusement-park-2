#include "pch.h"
#include "Menu.h"



Menu::Menu(const vector<string>& items, size_t top, size_t left) : items(items), top(top), left(left), activeMenu(0), maxSizeItems(0)
{
    maxSizeItems = FindMaxSizeItems();
}

Menu::Menu(const vector<string>& items) : items(items), activeMenu(0), maxSizeItems(0)
{
    size_t maxLengthStrMenu = 0;
    for (auto&& str : items)
    {
        if (str.size() > maxLengthStrMenu)
        {
            maxLengthStrMenu = str.size();
        }
    }
    maxLengthStrMenu += Console::GetWidthWindow() / 10;
    left = Console::GetWidthWindow() - maxLengthStrMenu;
    top = Console::GetHeightWindow() / 10;
    maxSizeItems = FindMaxSizeItems();
}

Menu::~Menu()
{
    Hide();
}

void Menu::UpdateItems(const vector<string>& items)
{
    activeMenu = 0;
    this->items = items;
    maxSizeItems = FindMaxSizeItems();
}

int Menu::ActivateMenu()
{
    size_t xBegin = Console::getXcoord();
    size_t yBegin = Console::getYcoord();
    Console::SaveColor();
    Console::ShowCursor(false);
    int keyMenu;
    
    for (int i = 0; i < items.size(); ++i)
    {
        if (i + top == activeMenu + top)
        {             
            Console::gotoxy(left - 2, top + i);
            cout << " ";
            Console::InvertColor();                
            Console::gotoxy(left, top + i);
            cout << items[i];
            Console::InvertColor();
        }
        else
        {
            Console::gotoxy(left, top + i);
            cout << items[i];
        }
    }

    // Ñïðàøèâàåì êëàâèøó è ñ÷èòûâàåì åå êîä
    keyMenu = _getch();
    if (keyMenu == -32)
    {
        keyMenu = _getch();
    }

    //Ïðîâåðÿåì íàæàòóþ êëàâèøó
    switch (keyMenu)
    {
        case ESC:
        {
            Console::gotoxy(xBegin, yBegin);
            Console::RestoreÑolor();
            Console::ShowCursor(true);
        
            return EXIT;
        }
        case DOWN:
        {
            if (activeMenu + top < top + items.size() - 1)
            {
                ++activeMenu;
                return activeMenu;
            }
            break;
        }
        case UP:
        {
            if (activeMenu + top > top)
            {
                --activeMenu;
                return activeMenu;
            }
            break;
        }
        case ENTER:
        {
            Console::gotoxy(left - 2, top + activeMenu);
            cout << '\x23';

            Console::gotoxy(xBegin, yBegin);
            Console::RestoreÑolor();
            Console::ShowCursor(true);
            return ENT;
        }
    }
        
}

void Menu::Hide()
{
    size_t bufX = Console::getXcoord();
    size_t bufY = Console::getYcoord();
    string bufDelStr = string(maxSizeItems + 2, ' ');
    for (int i = 0; i < items.size(); ++i)
    {
        Console::gotoxy(left - 2, top + i);
        cout << bufDelStr;
    }

    Console::gotoxy(bufX, bufY);
}

size_t Menu::getActiveItem()
{
    return activeMenu;
}

bool Menu::isDisplay() const
{
    return isDisp;
}

size_t Menu::FindMaxSizeItems()
{
    size_t maxSizeItemBuf;
    if (items.size() != 0)
    {
        maxSizeItemBuf = items[0].size();
    }
    else
    {
        maxSizeItemBuf = 0;
    }
    for (auto&& item : items)
    {
        if (item.size() > maxSizeItemBuf)
        {
            maxSizeItemBuf = item.size();
        }
    }

    return maxSizeItemBuf;
}




