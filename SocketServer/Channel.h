#pragma once
#include "BaseChannel.h"
#include "framework.h"


template <typename T>
class Channel : public BaseChannel
{
public:
	explicit Channel() : BaseChannel()
	{

	}
	void Join()
	{
		AfxSocketInit();
		sock.Create();
		sock.Connect("127.0.0.1", 1000-7);
		/*if (!sock.Connect("127.0.0.1", 1000 - 7))
		{
			throw runtime_error(GetLastErrorString());
		}
		else
		{
			cout << "подключился";
		}*/
	}
	using BaseChannel::Join;
};

template <>
class Channel<bool> : public BaseChannel
{
public:
	explicit Channel() : BaseChannel()
	{
		/*string buf1 = GetLastErrorString();
		sock.Create();
		string buf2 = GetLastErrorString();*/
	}
	//Channel<bool>& operator=(const Channel<bool>& channel) = default;
	/*static string GetLastErrorString(DWORD ErrorID = 0)
	{
		if (!ErrorID)
			ErrorID = GetLastError();
		if (!ErrorID)
			return string();

		LPSTR pBuff = nullptr;
		size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&pBuff, 0, NULL);
		string s(pBuff, size);
		LocalFree(pBuff);

		return s;
	}*/
	static void OpenPort(size_t port)
	{
		AfxSocketInit();
		server.Create(port);
	}
	static int WaitNewConnection()
	{
		return server.Listen();
	}
	void Join()
	{
		server.Accept(sock);
	}
	using BaseChannel::Join;


private:
	static CSocket server;
};


