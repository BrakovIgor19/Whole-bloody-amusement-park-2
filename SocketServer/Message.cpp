#include "pch.h"
#include "Message.h"



//int Message::clientID = 0;

/*void Message::send(CSocket& s, int to, int from, int type, const string& data)
{
	Message m(to, from, type, data);
	m.send(s);
}*/

Message::Message() : header{}, data("")
{

}

Message::Message(size_t to, size_t from, size_t type, const string& data) :
	header{ to, from, type, data.size() },
	data(data)
{

}

Message::Message(size_t to, size_t from, MessageTypes type, const string& data) :
	header{ to, from, static_cast<size_t>(type), data.size()},
	data(data)
{
}

Message::Message(MessageTypes type, const string& data) :
	header{0, 0, (size_t)type, data.size() },
	data(data)
{
}

Message::Message(size_t from, MessageTypes type, const string& data) :
	header{ 0, from, (size_t)type, data.size() },
	data(data)
{

}

Message::Message(size_t to, const string& data) :
	//header{ to, 0, static_cast<size_t>(MT_INIT), data.size() },
	data(data)
{
}

Message::Message(MessageTypes type) :
	header{0, 0, static_cast<size_t>(type), 0 },
	data("")
{
}

MessageHeader Message::GetHeader()
{
	return header;
}

string Message::GetDate()
{
	return data;
}



/*Message Message::send(int to, int type, const string& data)
{
	CSocket s;
	s.Create();
	if (!s.Connect("127.0.0.1", 12345))
	{
		throw runtime_error(GetLastErrorString());
	}
	Message m(to, clientID, type, data);
	m.send(s);
	if (m.receive(s) == MT_INIT)
	{
		clientID = m.header.to;
	}
	return m;
}*/

