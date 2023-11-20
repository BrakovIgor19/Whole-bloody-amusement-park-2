#pragma once
#include "Message.h"



class BaseChannel
{
public:
	explicit BaseChannel();
	
	/*BaseChannel(size_t port);
	BaseChannel(const BaseChannel& channel);*/

	void Send(const Message& message);
	SOCKET Forward();
	void Join(SOCKET forwardSock);


	void Close();
	Message Receive();
protected:
	CSocket sock;
};

