#pragma once
#include "../SocketServer/Channel.h"
#include "../SocketServer/Menu.h"
#include "../SocketServer/WindowChat.h"

#define _SECOND 10000000

// только после C++ 20 Sad Face)
using enum MessageTypes;

//BOOL WINAPI MyCtrlHandlerClose(DWORD dwCtrlType);

enum ItemMainMenu
{
	ITEM_GENERAL_CHAT,
	ITEM_PERSONAL_MESSAGES,
	ITEM_EXIT
};

class Client
{
	using CacheFriends = unordered_map<size_t, string>;
	using CacheMessages = unordered_map<int, vector<pair<size_t, string>>>;

	//friend BOOL WINAPI MyCtrlHandlerClose(DWORD dwCtrlType);
public:
	explicit Client();

private:

	// делаю поля статическими ради callback-а, Ужас не знаю как по другому(●´∀｀●)
	// Sad Face
	HANDLE hEventExit;
	HANDLE hTimer;
	static inline HANDLE hEventExitCtrl = CreateEvent(
		NULL, // атрибуты защиты
		FALSE, // тип события
		FALSE, // начальное состояние события
		"EventExitCtrl" // имя события
	);;
	static inline bool isValid = true;
	const string name;
	size_t id;
	CacheFriends cacheFriends;
	CacheMessages cacheMessages;
	Channel<int> chan;
	Channel<int> chanUpdate;
	void UpdateData(SOCKET forwardSock, WindowChat& winChat);
	void UpdateTimer();
	void TimeOut();
	static BOOL __stdcall HandlerCtrlCloseWindow(DWORD dwCtrlType);
	vector<string> SplitString(const string& str, string delimiter = ";");
	CacheFriends StringToCacheFriends(const vector<string>& vecStr);
	vector<string> CacheFriendsToItemsMenu();
	vector<string> CacheMessagesToVecStr(int id);
	size_t activeItemMainMenu;
	size_t activeItemFriendMenu;
	unordered_map<size_t, size_t> itemToidMap;
	

};

