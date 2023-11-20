#include "pch.h"
#include "Server.h"

//size_t Server::maxId = 0;
//CRITICAL_SECTION Server::cs;

Server::Server()
{
	//SetCurrentDirectory("../Csharp/bin/Debug");
	system("cls");
	SetConsoleTitleW(L"Сервер");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// инициализация критической секции
	InitializeCriticalSection(&cs);

	try
	{
		connection C("dbname = postgres user = postgres password = 12345 \
					  hostaddr = 127.0.0.1 port = 5432");
		if (C.is_open())
		{
			cout << C.dbname() << endl << " Урра, да здравствует postgres, И пусть взлетит твоя ракета и заведётся твой танк" << endl;
		}
		else
		{
			cout << "Can't open database" << endl;
		}
		

	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		cout << "Sad face postgres" << "Говорят ты спишь с другими, но всё равно я тебя люблю";
	}


	

	Channel<bool>::OpenPort(1000-7);
	while (true)
	{
		if (!Channel<bool>::WaitNewConnection())
		{
			break;
		}
		Channel<bool> chanOut;
		chanOut.Join();
		if (!Channel<bool>::WaitNewConnection())
		{
			break;
		}
		Channel<bool> chanIn;
		chanIn.Join();
		thread t(&Server::ProcessClient, this, chanOut.Forward(), chanIn.Forward());
		t.detach();
	}
}

Server::~Server()
{
	// мощное уничтожение объекта критическая секция
	DeleteCriticalSection(&cs);

}

pair<size_t, shared_ptr<Session>> Server::AddSession()
{
	// вход в критическую секцию
	EnterCriticalSection(&cs);

	auto session = make_pair(maxId++, make_shared<Session>());
	sessions.insert(session);

	// выход из критической секции
	LeaveCriticalSection(&cs);

	return session;
}

void Server::ProcessClient(SOCKET forwardSockOut, SOCKET forwardSockIn)
{
	// не спасёт!!!
	//size_t bufId = maxId++;
	//sessions.emplace(bufId, Session());

	// Подключаемся к базе данных

	auto pairSession = AddSession();
	pairSession.second->chan.Join(forwardSockOut);
	Channel<bool> chanInBuf;
	chanInBuf.Join(forwardSockIn);
	while (pairSession.second->isValid)
	{
		Message m = pairSession.second->chan.Receive();
		switch ((MessageTypes)m.GetHeader().type)
		{
			case MT_INIT:
			{
				/*auto session = make_shared<Session>(++maxID, m.data);
				sessions[session->id] = session;
				Message::send(s, session->id, MR_BROKER, MT_INIT);*/

				// Инициализация пользователя
				pairSession.second->name = m.GetDate();
				cout << "Пользователь: " + pairSession.second->name + " авторизован" << endl;
				pairSession.second->chan.Send(Message(MT_CONFIRM, "0" + to_string(pairSession.first)));
				thread t(&Server::ProcessUpdateDataClient, this, pairSession.first, chanInBuf.Forward());
				t.detach();

				// Отправление сообщение клиентам на обновление списка пользователей
				for (auto&& [id, ptrSession] : sessions)
				{
					ptrSession->AddMessageToQueue(Message(MT_UPDATE_USER_LIST, getListUsersToString()));
					SetEvent(ptrSession->hEventUpdateDataClient);
				}

				break;
			}
			case MT_EXIT:
			{
				/*sessions.erase(m.header.from);
				Message::send(s, m.header.from, MR_BROKER, MT_CONFIRM);
				break;*/
				// БЛиин ну тут сложна, сложный момент пока оставлю, так это же временно) 
				// Sad Face (´｡•ᵕ•｡`)
				
				pairSession.second->chan.Send(Message(MT_CONFIRM, "0"));
				cout << "Пользователь: " + pairSession.second->name + " отключился" << endl;

				
				// Отправление сообщение клиентам на обновление списка пользователей
				for (auto&& [id, ptrSession] : sessions)
				{
					if (id != pairSession.first)
					{
						ptrSession->AddMessageToQueue(Message(MT_UPDATE_USER_LIST, getListUsersToString({ pairSession.first })));
						//SetEvent(ptrSession->hEventUpdateDataClient);
					}
				}
				// Героический цикл в деле)
				While:
				if (sessions[pairSession.first]->messages.empty())
				{
					goto ExitWhile;
				}
				goto While;
				ExitWhile:

				pairSession.second->isValid = false;
				//SetEvent(pairSession.second->hEventUpdateDataClient);
				// Тут ещё по идее нужно дождаться выхода второго потока (◕‿◕)


				break;
			}
			// пока непонятно можно или нужно так делать или вообще не стоит
			
			case MT_MESSAGE:
			{
				sessions[m.GetHeader().to]->AddMessageToQueue(m);
				//SetEvent(pairSession.second->hEventUpdateDataClient);
				pairSession.second->chan.Send(Message(MT_CONFIRM, "0"));

				break;
			}
			case MT_MESSAGE_ALL:
			{
				for (auto&& [id, ptrSession] : sessions)
				{
					if (id != pairSession.first)
					{
						ptrSession->AddMessageToQueue(m);
						//SetEvent(ptrSession->hEventUpdateDataClient);
					}
				}
				pairSession.second->chan.Send(Message(MT_CONFIRM, "0"));

				break;
			}
		}
	}
	// Тут ещё по идее нужно дождаться выхода второго потока (◕‿◕)
	// Сделай хотя бы событие неудачник 
	//Sleep(2000);
	WaitForSingleObject(pairSession.second->hEventExit, INFINITE);
	pairSession.second->chan.Close();
	sessions.erase(pairSession.first);
}

void Server::ProcessUpdateDataClient(size_t id, SOCKET forwardIn)
{
	// пока не ясно насчёт этого) нужно ли и если да, то всё ли так просто, хехехехехе
	//WaitForSingleObject(sessions[id]->hEventUpdateDataClient, INFINITE);
	sessions[id]->chanUpdate.Join(forwardIn);
	while (sessions[id]->isValid)
	{
		//WaitForSingleObject(sessions[id]->hEventUpdateDataClient, INFINITE);
		if (!sessions[id]->messages.empty())
		{
			Message m = sessions[id]->getMessage();
			switch ((MessageTypes)m.GetHeader().type)
			{
				// Чисто для логинга (caursed Logrus 2023)
				case MT_UPDATE_USER_LIST:
				{
					cout << "Отправил " << sessions[id]->name << " обновление списка пользователей" << endl;
					break;
				}
				case MT_MESSAGE_ALL:
				{
					
					cout << sessions[m.GetHeader().from]->name << "Отправил сообщение для всех " << endl;
					break;
				}
				case MT_MESSAGE:
				{

					cout << sessions[id]->name << " отправил сообщение " << m.GetDate() << " " << sessions[m.GetHeader().to]->name << endl;
					break;
				}
				default:
				{
					break;
				}
			}
			sessions[id]->chanUpdate.Send(m);
		}
		else
		{
			//ResetEvent(sessions[id]->hEventUpdateDataClient);
		}
	}
	//sessions[id]->chanUpdate.Send(Message(MT_EXIT, "0"));
	cout << "Потока обновлений " << sessions[id]->name << ": 1000 - 7" << endl;
	sessions[id]->chanUpdate.Close();
	SetEvent(sessions[id]->hEventExit);
}

string Server::getListUsersToString(vector<size_t> exceptions, char separator)
{
	string listUsers;
	for (auto&& [id, ptrSession] : sessions)
	{
		auto it = find(exceptions.begin(), exceptions.end(), id);
		if (it == exceptions.end())
		{
			listUsers.append(string(to_string(id) + separator));
			listUsers.append(string(ptrSession->name + separator));
		}
	}
	listUsers.pop_back();
	return listUsers;
}

//size_t Server::getEvent(DWORD nCount, const HANDLE* lpHandles)
//{
//	return static_cast<size_t>(WaitForMultipleObjects(nCount, lpHandles, FALSE, INFINITE) - WAIT_OBJECT_0);
//}

