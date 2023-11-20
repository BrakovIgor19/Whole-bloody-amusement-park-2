#include "pch.h"
#include "BaseChannel.h"

BaseChannel::BaseChannel() 
{
	//AfxSocketInit();
}

void BaseChannel::Send(const Message& message)
{
	sock.Send(&message.header, sizeof(MessageHeader));
	if (message.header.size)
	{
		sock.Send(message.data.c_str(), (int)message.header.size);
	}
}

SOCKET BaseChannel::Forward()
{
	return sock.Detach();
}

void BaseChannel::Join(SOCKET forwardSock)
{
	sock.Attach(forwardSock);
}

void BaseChannel::Close()
{
	sock.Close();
}

Message BaseChannel::Receive()
{
	Message message;
	sock.Receive(&message.header, sizeof(MessageHeader));
	if (message.header.size)
	{
		vector <char> v(message.header.size);
		sock.Receive(&v[0], (int)message.header.size);
		message.data = string(&v[0], message.header.size);
	}
	return message;
}
