#include "pch.h"
#include "WindowChat.h"


WindowChat::WindowChat(size_t left, size_t top, size_t right, size_t bottom, char frameSymbol) :
    left(left), top(top), right(right), bottom(bottom), frameSymbol(frameSymbol), height(bottom - top - 1), width(right - left - 1), isDisp(false)
{
    history.reserve(150);
}

WindowChat::WindowChat() :
    left(2), top(2), right(80), bottom(20), frameSymbol('#'), height(bottom - top - 1), width(right - left - 1), isDisp(false)
{
    history.reserve(150);
}

WindowChat::~WindowChat()
{
    Hide();
}

void WindowChat::DrawData()
{
    string bufEmptyStr;
    for (int i = 0; i < width; ++i)
    {
        bufEmptyStr += " ";
    }
    for (int i = 0; i < height; ++i)
    {
        Console::gotoxy(left + 1, top + 1 + i);
        cout << bufEmptyStr;
    }
    if (displayedData.size() >= height)
    {
        for (int i = 0; i < height; ++i)
        {
            Console::gotoxy(left + 1, top + 1 + i);
            cout << displayedData[i];
        }
    }
    else
    {
        for (int i = 0; i < displayedData.size(); ++i)
        {
            Console::gotoxy(left + 1, top + 1 + i);
            cout << displayedData[i];
        }
    }
}

void WindowChat::Display()
{
    ConsoleFormatOutIn::WriteTextCenterThisCoord(left + (width + 2) / 2, top - 2, "Окно чата");
    Console::gotoxy(left, top);
    DrawFrame(width + 2, height + 2);
    displayedData.reserve(height);
    DrawData();
    isDisp = true;
}

bool WindowChat::isDisplay() const
{
    return isDisp;
}

void WindowChat::Hide()
{
    size_t bufX = Console::getXcoord();
    size_t bufY = Console::getYcoord();
    Console::ShowCursor(false);
    for (int i = 0; i < height + 4; i++)
    {
        Console::gotoxy(left, top - 2 + i);
        for (int j = 0; j < width + 2; ++j)
        {
            cout << " ";
        }
    }
    Console::gotoxy(bufX, bufY);
    Console::ShowCursor(true);
    isDisp = false;
}

string WindowChat::InputMessage()
{
    size_t bufX = Console::getXcoord();
    size_t bufY = Console::getYcoord();
    Console::gotoxy(left, bottom);
    DrawFrame(width + 2, 5);
    Console::gotoxy(left + 2, bottom + 2);
    string message;
    
    int ch = 0;
    size_t countChar = 0;
    bool flag = true;
    while (flag)
    {
        ch = _getch();
        if (ch == -32)
        {
            ch = _getch();
        }
        switch (ch)
        {
        case 8:
        {
            if (countChar > 0)
            {
                Console::gotoxy(left + 2 + countChar - 1, bottom + 2);
                cout << " ";
                Console::gotoxy(left + 2 + countChar - 1, bottom + 2);
                message.pop_back();
                --countChar;
            }
            break;
        }
        case 13:
        {
            flag = false;
            break;
        }
        default:
        {
            if (countChar < width - 2)
            {
                ++countChar;
                message += (char)ch;
                cout << (char)ch;
            }
            break;
        }
        }
    }
    Console::ShowCursor(false);
    for (int i = 0; i < 4; i++)
    {
        Console::gotoxy(left, bottom + 1 + i);
        for (int j = 0; j < width + 2; ++j)
        {
            cout << " ";
        }
    }
    Console::gotoxy(bufX, bufY);
    Console::ShowCursor(true);

    return message;
}

void WindowChat::LoadLatestMessages(const vector<string>& str)
{
    string bufEmptyStr = string(width, ' ');
    for (int i = 0; i < height; ++i)
    {
        Console::gotoxy(left + 1, top + 1 + i);
        cout << bufEmptyStr;
    }
    size_t countChar = 0;
    size_t maxChar = width * height;
    size_t maxMessage = 0;
    for (auto it = str.rbegin(); countChar <= maxChar && it != str.rend(); ++it)
    {
        if (countChar + (*it).size() + (width - (*it).size() % width) < maxChar)
        {
            countChar += (*it).size() + (width - (*it).size() % width);
            ++maxMessage;
        }
        else
        {
            break;
        }
    }
    if (maxMessage > 0)
    {
        size_t buf = 0;
        for (int i = str.size() - maxMessage; i < str.size(); ++i)
        {
            size_t count = 0;
            while (count < str[i].size())
            {
                if (count % width == 0)
                {
                    Console::gotoxy(left + 1, top + 1 + buf);
                    ++buf;
                }
                cout << str[i][count];
                ++count;
            }
            cout << endl;
        }
    }
}

void WindowChat::DrawFrame(size_t width, size_t height)
{
    setlocale(LC_CTYPE, "C");
    int bufx, bufy;
    for (int i = 0; i < width; ++i)
    {
        cout << frameSymbol;
    }
    bufx = Console::getXcoord() - 1; bufy = Console::getYcoord();
    for (int i = 0; i < height; ++i)
    {
        Console::gotoxy(bufx, bufy + i);
        cout << frameSymbol << endl;
    }
    Console::gotoxy(bufx - (width - 1), bufy);
    bufx = Console::getXcoord(); bufy = Console::getYcoord();
    for (int i = 0; i < height; ++i)
    {
        Console::gotoxy(bufx, bufy + i);
        cout << frameSymbol << endl;
    }
    Console::gotoxy(bufx, bufy + (height - 1));
    for (int i = 0; i < width; ++i)
    {
        cout << frameSymbol;
    }
    setlocale(LC_CTYPE, ".1251");
}