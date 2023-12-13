#pragma once
#include "Channel.h"

class Session
{
	friend class Server;
public:

	//CCriticalSection cs;
	explicit Session(string firstName, string lastName);

	explicit Session();

	explicit Session(Session&&) = default;

	// очень хочется move-приколы тут намутить, хехехехх <]:-o)
	void AddMessageToQueue(const Message& m);
	//{
	//	/*CSingleLock lock(&cs, TRUE);*/
	//	messages.push(m);
	//}

	Message getMessage();
	//{
	//	/*CSingleLock lock(&cs, TRUE);
	//	if (messages.empty())
	//	{
	//		Message::send(s, id, MR_BROKER, MT_NODATA);
	//	}
	//	else
	//	{
	//		messages.front().send(s);
	//		messages.pop();
	//	}*/
	//}
private:
	bool isValid;
	size_t id;
	string firstName;
	string lastName;
	string nameAvatar;
	queue<Message> messages;
	Channel<bool> chan;
	Channel<bool> chanUpdate;
	HANDLE hEventUpdateDataClient;
	HANDLE hEventExit;
};

