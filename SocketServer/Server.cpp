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



vector<string> Server::SplitString(const string& str, string delimiter)
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

Server::~Server()
{
	// мощное уничтожение объекта критическая секция
	DeleteCriticalSection(&cs);

}


pair<size_t, shared_ptr<Session>> Server::AddSession()
{
	// вход в критическую секцию
	EnterCriticalSection(&cs);

	auto session = make_pair(++bufId, make_shared<Session>());
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
	//connection connectDB;
	//try
	//{
	connection connectDB = connection("dbname = vk1000-7 user = 1000-7 password = 1000-7 \
							  hostaddr = 127.0.0.1 port = 5432");
	

	//	if (connectDB.is_open())
	//	{
	//		cout << connectDB.dbname() << endl << " Урра, да здравствует postgres, И пусть взлетит твоя ракета и заведётся твой танк" << endl;
	//	}
	//	else
	//	{
	//		cout << "Can't open database" << endl;
	//	}
	////	//nontransaction N(connectDB);

	/*}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		cout << "Sad face postgres" << "Говорят ты спишь с другими, но всё равно я тебя люблю";
	}*/
	//nontransaction N(connectDB);

	auto pairSession = AddSession();
	pairSession.second->chan.Join(forwardSockOut);
	Channel<bool> chanInBuf;
	chanInBuf.Join(forwardSockIn);
	bool isPlayUpdateProcess = false;
	while (pairSession.second->isValid)
	{
		Message m = pairSession.second->chan.Receive();
		switch ((MessageTypes)m.GetHeader().type)
		{
			case MT_AUTHORIZATION:
			{
				work W(connectDB);
				vector<string> bufMailPassword = SplitString(m.GetDate(), ";");

				string sqlStr = "SELECT password, id_user FROM mailpassword WHERE mail = '" + bufMailPassword[0] + "'";
				const char* sql = sqlStr.c_str();
				//nontransaction N(connectDB);
				result R(W.exec(sql));
				if (!R.empty() && R[0][0].as<string>() == bufMailPassword[1])
				{
					isPlayUpdateProcess = true;
					string sqlStr = string("SELECT Users.id, Users.firstname, Users.lastname, Users.nameAvatar FROM Users WHERE id = ") + to_string(R[0][1].as<int>());
					const char* sql = sqlStr.c_str();
					result R(W.exec(sql));		
					pairSession.second->id = R[0][0].as<int>();
					pairSession.second->firstName = R[0][1].as<string>();
					pairSession.second->lastName = R[0][2].as<string>();
					pairSession.second->nameAvatar = R[0][3].as<string>();
					string bufStr = to_string(pairSession.second->id) + ";" + pairSession.second->firstName + ";" + pairSession.second->lastName + ";" + pairSession.second->nameAvatar;
					pairSession.second->chan.Send(Message(MT_AUTHORIZATION_SUCCESS, bufStr));
					//for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
					//	//cout << "password = " << c[0].as<string>() << endl;
					//}
					// Инициализация пользователя
					//pairSession.second->name = m.GetDate();
					cout << "Пользователь: " + R[0][1].as<string>() + " " + R[0][2].as<string>() + " авторизован" << endl;
					//pairSession.second->chan.Send(Message(MT_CONFIRM, "0" + to_string(pairSession.first)));
					thread t(&Server::ProcessUpdateDataClient, this, pairSession.first, chanInBuf.Forward());
					t.detach();
					// Отправление сообщение клиентам на обновление списка пользователей

					for (auto&& [id, ptrSession] : sessions)
					{
						ptrSession->AddMessageToQueue(Message(MT_UPDATE_USER_LIST, getAllConvAndActiveUserConv(ptrSession->id, W, {})));
						SetEvent(ptrSession->hEventUpdateDataClient);
					}
					sqlStr = string("SELECT Users_Conversations.id_conversation FROM Users_Conversations WHERE Users_Conversations.id_user = " + to_string(pairSession.second->id) + ";");
					sql = sqlStr.c_str();
					result R2(W.exec(sql));
					for (result::const_iterator c = R2.begin(); c != R2.end(); ++c)
					{
						onlineUsersInConv[c[0].as<int>()].insert(pairSession.first);
					}
				}	
				else
				{
					pairSession.second->chan.Send(Message(MT_AUTHORIZATION_FAILED));
					chanInBuf.Send(Message(MT_EXIT));
					pairSession.second->isValid = false;
					connectDB.close();
				}
				break;
			}
			case MT_EXIT:
			{
				work W(connectDB);
				/*sessions.erase(m.header.from);
				Message::send(s, m.header.from, MR_BROKER, MT_CONFIRM);
				break;*/
				// БЛиин ну тут сложна, сложный момент пока оставлю, так это же временно) 
				// Sad Face (´｡•ᵕ•｡`)
				//chanInBuf.Send(Message(MT_EXIT));
				pairSession.second->chan.Send(Message(MT_CONFIRM));
				//cout << m.GetDate() << endl;
				cout << "Пользователь: " + pairSession.second->firstName + " " + pairSession.second->lastName + " отключился" << endl;

				//nontransaction N(connectDB);
				// Отправление сообщение клиентам на обновление списка пользователей
				for (auto&& [id, ptrSession] : sessions)
				{
					if (id != pairSession.first)
					{
						ptrSession->AddMessageToQueue(Message(MT_UPDATE_USER_LIST, getAllConvAndActiveUserConv(ptrSession->id, W, { pairSession.second->id })));
						//SetEvent(ptrSession->hEventUpdateDataClient);
					}
				}
				pairSession.second->AddMessageToQueue(Message(MT_EXIT));
				// Героический цикл в деле)
				While:
				if (sessions[pairSession.first]->messages.empty())
				{
					goto ExitWhile;
				}
				goto While;
				ExitWhile:
				for (auto&& [id, set] : onlineUsersInConv)
				{
					set.erase(pairSession.first);
				}
				pairSession.second->isValid = false;
				//SetEvent(pairSession.second->hEventUpdateDataClient);
				// Тут ещё по идее нужно дождаться выхода второго потока (◕‿◕)

				break;
			}
			// пока непонятно можно или нужно так делать или вообще не стоит
			
			case MT_MESSAGE:
			{
				work W(connectDB);
				auto bufHead = m.GetHeader();
				string bufStr = pairSession.second->firstName + " " + pairSession.second->lastName + ": ";
				Message mbuf = Message(bufHead.to, bufHead.from, bufHead.type, bufStr + m.GetDate());
				for (auto&& idSession : onlineUsersInConv[m.GetHeader().to])
				{
					if (idSession != pairSession.first)
					{
						sessions[idSession]->AddMessageToQueue(mbuf);
					}
					else
					{
						cout << bufStr + " отправила сообщение " + m.GetDate() + ": в беседу " + to_string(m.GetHeader().to) << endl;
					}

				}
				string from = to_string(m.GetHeader().from);
				string to = to_string(m.GetHeader().to);
				string data = m.GetDate();
				string sqlStr = "INSERT INTO Messages(data, id_conversation, id_user) VALUES ('" + data + "', " + to + ", " + from + ");";
				const char* sql = sqlStr.c_str();
				W.exec(sql);
				W.commit();
				SetEvent(pairSession.second->hEventUpdateDataClient);
				pairSession.second->chan.Send(Message(MT_CONFIRM, "0"));

				break;
			}
			case MT_MESSAGE_ALL:
			{
				//for (auto&& [id, ptrSession] : sessions)
				//{
				//	if (id != pairSession.first)
				//	{
				//		ptrSession->AddMessageToQueue(m);
				//		//SetEvent(ptrSession->hEventUpdateDataClient);
				//	}
				//}
				//pairSession.second->chan.Send(Message(MT_CONFIRM, "0"));

				break;
			}
		}
	}
	// Тут ещё по идее нужно дождаться выхода второго потока (◕‿◕)
	// Сделай хотя бы событие неудачник 
	//Sleep(2000);
	if (isPlayUpdateProcess)
	{
		WaitForSingleObject(pairSession.second->hEventExit, INFINITE);
	}
	pairSession.second->chan.Close();
	sessions.erase(pairSession.first);
	chanInBuf.Close();
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
					cout << "Отправил " << sessions[id]->firstName + " " + sessions[id]->lastName << " обновление списка пользователей" << endl;
					break;
				}
				case MT_MESSAGE_ALL:
				{
					
					cout << sessions[m.GetHeader().from]->firstName + " " + sessions[m.GetHeader().from]->lastName << "Отправил сообщение для всех " << endl;
					break;
				}
				case MT_MESSAGE:
				{
					cout << sessions[id]->firstName + " " + sessions[id]->lastName << " получил сообщение " << ": в беседу " << m.GetDate() << endl;
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
	cout << "Поток обновлений пользователя " << sessions[id]->firstName + " " + sessions[id]->lastName << ": 1000 - 7" << endl;
	sessions[id]->chanUpdate.Close();
	SetEvent(sessions[id]->hEventExit);
}

string Server::getAllConvAndActiveUserConv(size_t id, work& W, vector<size_t> exceptions)
{
	string bufConv;
	string id_user = to_string(id);
	string sqlStr = "WITH inConv(id, is_private_messages) AS\
	(SELECT Conversations.id, Conversations.is_private_messages FROM Users_Conversations\
		INNER JOIN Conversations ON Conversations.id = id_conversation\
		WHERE id_user = " + id_user + " AND is_private_messages = TRUE), \
		bufT(id_user, id_conv, is_private_messages) AS\
		(SELECT Users_Conversations.id_user, Users_Conversations.id_conversation, inConv.is_private_messages FROM inConv\
			INNER JOIN Users_Conversations ON inConv.id = Users_Conversations.id_conversation\
			WHERE id_user != " + id_user + "),\
		bufT2(name, id_user) AS\
		(SELECT CONCAT(Users.firstname, ' ', Users.lastname), Users.id FROM Users\
			INNER JOIN bufT ON Users.id = bufT.id_user)\
		SELECT Conversations.id, Conversations.name, Users_Conversations.id_user, Conversations.is_private_messages FROM Users_Conversations\
		INNER JOIN Conversations ON Conversations.id = id_conversation\
		WHERE id_user = " + id_user + " AND is_private_messages = FALSE\
		UNION ALL\
		SELECT bufT.id_conv, bufT2.name, bufT2.id_user, bufT.is_private_messages FROM bufT\
		INNER JOIN bufT2 ON bufT.id_user = bufT2.id_user;";
	const char* sql = sqlStr.c_str();
	result R(W.exec(sql));
	for (result::const_iterator c = R.begin(); c != R.end(); ++c)
	{
		if (c[3].as<bool>())
		{
			auto it = find(exceptions.begin(), exceptions.end(), c[2].as<int>());
			for (auto&& [idSession, session] : sessions)
			{
				if (it == exceptions.end() && c[2].as<int>() == session->id)
				{
					bufConv.append(string(to_string(c[0].as<int>()) + ';'));
					bufConv.append(string(c[1].as<string>() + ';'));
					break;
				}
			}
		}
		else
		{
			bufConv.append(string(to_string(c[0].as<int>()) + ';'));
			bufConv.append(string(c[1].as<string>() + ';'));
		}
	}
	return bufConv;
}




