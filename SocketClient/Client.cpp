#include "pch.h"
#include "Client.h"

//bool Client::isValid = true;

BOOL __stdcall Client::HandlerCtrlCloseWindow(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		isValid = false;
		//cin.putback('d');
		/*reinterpret_cast<void*>(Client::*UpdateData)*/
		WaitForSingleObject(hEventExitCtrl, INFINITE);
	}
	return TRUE;
}

vector<string> Client::SplitString(const string& str, string delimiter)
{
	// C++20 в деле))) ехеееххехехех
	/*auto split = hello
		| std::ranges::views::split(' ')
		| std::ranges::views::transform([](auto&& str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });*/

	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
		token = str.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(str.substr(pos_start));
	return res;
}

unordered_map<size_t, string> Client::StringToCacheFriends(const vector<string>& vecStr)
{
	unordered_map<size_t, string> cacheFriends;
	cacheFriends.reserve(vecStr.size());
	for (size_t i = 0; i < vecStr.size(); i += 2)
	{
		cacheFriends.emplace(stoi(vecStr[i]), vecStr[i + 1]);
	}

	return cacheFriends;
}

vector<string> Client::CacheFriendsToItemsMenu()
{
	vector<string> item;
	item.reserve(cacheFriends.size());
	for (auto&& [id, nameFriend] : cacheFriends)
	{
		item.push_back(nameFriend);
	}
	return item;
}

vector<string> Client::CacheMessagesToVecStr(int id)
{
	vector<string> vecStr;
	vecStr.reserve(cacheMessages[id].size());
	for (auto&& [id, message] : cacheMessages[id])
	{
		vecStr.push_back(cacheFriends.at(id) + ": " + message);
	}
	return vecStr;
}


Client::Client() //: isValid(true)
{
	/*void (Client::*UpdateData)(int) = &(Client::UpdateData);
	reinterpret_cast<void*>(Client::*UpdateData()))*/
	SetConsoleCtrlHandler(HandlerCtrlCloseWindow, TRUE);
	hEventExit = CreateEvent(
		NULL, // атрибуты защиты
		FALSE, // тип события
		FALSE, // начальное состояние события
		"EventExit" // имя события
	);
	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	// Настройка)
	//SetCurrentDirectory("../Csharp/bin/Debug");
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Подозрительная фигня
	// Соединяемся с сервером
	chan.Join();
	Channel<int> bufChannel;
	bufChannel.Join();

	// Пытаемся авторизоваться
	TCHAR title[MAX_PATH];
	GetConsoleTitle(title, MAX_PATH);
	//chan.Send(Message(MT_INIT, string(title)));
	Message m = chan.Receive();
	if (m.GetDate()[0] == '0')
	{
		id = stoi(m.GetDate().substr(1));
		WindowChat winChat = WindowChat();
		thread t(&Client::UpdateData, this, bufChannel.Forward(), ref(winChat));
		t.detach();
		thread time(&Client::TimeOut, this);
		time.detach();
		Menu mainMenu = Menu({ "Общий чат", "Личные сообщения", "1000-7" });
		Menu friendsMenu = Menu({ string(title) });
		winChat.Display();
		winChat.LoadLatestMessages(CacheMessagesToVecStr(-1));
		
		activeItemMainMenu = 0;

		// Героический пользовательский цикл
		while (isValid)
		{
			int activePrevItem = mainMenu.getActiveItem();
			int activeNextItem = mainMenu.ActivateMenu();
			//UpdateTimer();
			switch (activeNextItem)
			{
				case ITEM_GENERAL_CHAT:
				{
					activeItemMainMenu = 0;
					winChat.Display();
					winChat.LoadLatestMessages(CacheMessagesToVecStr(-1));
					break;
				}
				case ENT:
				{
					switch (activePrevItem)
					{
						case ITEM_GENERAL_CHAT:
						{
							string buf = winChat.InputMessage();
							chan.Send(Message(id, MT_MESSAGE_ALL, buf));
							if (chan.Receive().GetDate() == "0")
							{
								cacheMessages[-1].emplace_back(id, buf);
								winChat.LoadLatestMessages(CacheMessagesToVecStr(-1));
							}
							else
							{

							}
							break;
						}
						case ITEM_EXIT:
						{
							activeItemMainMenu = -1;
							winChat.Hide();
							mainMenu.Hide();
							isValid = false;
							break;
						}
						case ITEM_PERSONAL_MESSAGES:
						{
							activeItemMainMenu = -1;
							mainMenu.Hide();
							winChat.Display();
							// менять потом, придумай что-нибудь получше!!!!!!!!!
							/*vector<string> friends;
							friends.reserve(cacheFriends.size());
							for (auto&& [id, name] : cacheFriends)
							{
								friends.push_back(name);
							}*/
							itemToidMap.clear();
							itemToidMap.reserve(cacheFriends.size());
							size_t bufCount = 0;
							for (auto&& [id, name] : cacheFriends)
							{
								itemToidMap.emplace(bufCount, id);
								++bufCount;
							}
							friendsMenu.UpdateItems(CacheFriendsToItemsMenu());
							bool flag = true;
							while (flag)
							{
								activePrevItem = friendsMenu.getActiveItem();
								activeItemFriendMenu = activePrevItem;
								activeNextItem = friendsMenu.ActivateMenu();
								//UpdateTimer();
								switch (activeNextItem)
								{
								case ENT:
								{
									string buf = winChat.InputMessage();
									chan.Send(Message(itemToidMap[activePrevItem], id, MT_MESSAGE, buf));
									if (chan.Receive().GetDate() == "0")
									{
										if (id != itemToidMap[activePrevItem])
										{
											cacheMessages[itemToidMap[activePrevItem]].emplace_back(id, buf);
										}
										winChat.LoadLatestMessages(CacheMessagesToVecStr(itemToidMap[activePrevItem]));
									}
									else
									{

									}
									break;
								}
								case EXIT:
								{
									winChat.Hide();
									friendsMenu.Hide();
									flag = false;
									break;
								}
								default:
								{
									if (activeNextItem != activePrevItem)
									{
										activeItemFriendMenu = friendsMenu.getActiveItem();
										winChat.LoadLatestMessages(CacheMessagesToVecStr(itemToidMap[activeNextItem]));
									}
									break;
								}
								}								
							}
							break;
						}						
					}
					break;
				}
				case EXIT:
				{
					activeItemMainMenu = -1;
					winChat.Hide();
					mainMenu.Hide();
					isValid = false;
					break;
				}
				default:
				{
					activeItemMainMenu = -1;
					if (winChat.isDisplay())
					{
						winChat.Hide();
					}
					break;
				}				
			}
		}
	}
	else
	{
		cout << "Sad Face";
	}

	// Обработка закрытия клиента
	chan.Send(Message(MT_EXIT));
	if (chan.Receive().GetDate() == "0")
	{
		/*cout << "1000-7";*/
	}
	else
	{
		/*cout << "Sad Face";*/
	}
	WaitForSingleObject(hEventExit, INFINITE);
	// Сделай событие хотя бы неудачник !!!
	//Sleep(2000); 
	chan.Close();
	SetEvent(hEventExitCtrl);
}

void Client::UpdateData(SOCKET forwardSock, WindowChat& winChat)
{
	chanUpdate.Join(forwardSock);
	while (isValid)
	{
		Message m = chanUpdate.Receive();
		switch ((MessageTypes)m.GetHeader().type)
		{
		/*case MT_EXIT:
		{
			break;
		}*/
		case MT_UPDATE_USER_LIST:
		{
			cacheFriends = StringToCacheFriends(SplitString(m.GetDate()));

			break;
		}
		case MT_MESSAGE:
		{
			cacheMessages[m.GetHeader().from].emplace_back(m.GetHeader().from, m.GetDate());
			if (itemToidMap[activeItemFriendMenu] == m.GetHeader().from)
			{
				winChat.LoadLatestMessages(CacheMessagesToVecStr(m.GetHeader().from));
			}
			/*string strName;
			bool flag = false;
			for (auto&& [id, name] : cacheFriends)
			{
				if (id == m.GetHeader().from)
				{
					flag = true;
					strName = name;
					break;
				}
			}
			if (flag)
			{
				cout << "Сообщение для меня от " << strName << ": " << m.GetDate() << endl;
			}
			else
			{
				cout << "Сообщение для меня от " << "*** знает кого" << ": " << m.GetDate() << endl;
			}*/
			break;
		}
		case MT_MESSAGE_ALL:
		{
			cacheMessages[-1].emplace_back(m.GetHeader().from, m.GetDate());
			if (activeItemMainMenu == 0)
			{
				winChat.LoadLatestMessages(CacheMessagesToVecStr(-1));
			}
			/*string strName;
			bool flag = false;
			for (auto&& [id, name] : cacheFriends)
			{
				if (id == m.GetHeader().from)
				{
					flag = true;
					strName = name;
					break;
				}
			}*/
			/*if (flag)
			{
				cout << "Сообщение для всех от " << strName << ": " << m.GetDate() << endl;
			} 
			else
			{
				cout << "Сообщение для всех от " << "*уй знает кого" << ": " << m.GetDate() << endl;
			}*/
			break;
		}
		default:
		{

			break;
		}
		}
	}
	/*cout << "Потока обновлений: 1000-7" << endl;*/
	chanUpdate.Close();
	SetEvent(hEventExit);
}

void Client::UpdateTimer()
{
	//_int64 qwTimeInterval = -10 * _SECOND;
	//SetWaitableTimer(
	//	hTimer, // дескриптор таймера
	//	(LARGE_INTEGER*)&qwTimeInterval, // временной интервал
	//	0, // непериодический таймер
	//	NULL, // процедуры завершения нет
	//	NULL, // параметров к этой процедуре нет
	//	FALSE // режим сбережения энергии не устанавливать
	//);
}

void Client::TimeOut()
{
	//WaitForSingleObject(hTimer, INFINITE);
	////isValid = false;
	//ExitProcess(0);
}




