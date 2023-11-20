#pragma once

#include <functional>
#include "resource.h"
#include "framework.h"
#include "Channel.h"
#include "Session.h"
#include <pqxx/pqxx>

using namespace pqxx;
using enum MessageTypes;


class Server
{
public:
	explicit Server();
	~Server();
	pair<size_t, shared_ptr<Session>> AddSession();

private:
	static inline size_t maxId = 0;
	static inline CRITICAL_SECTION cs;
	unordered_map<size_t, shared_ptr<Session>> sessions;
	void ProcessClient(SOCKET forwardSockOut, SOCKET forwardSockIn);
	void ProcessUpdateDataClient(size_t id, SOCKET forwardIn);
	// переделать на вариадическую функцию или не надо?
	string getListUsersToString(vector<size_t> exceptions = {}, char separator = ';');
	//size_t getEvent(DWORD nCount, const HANDLE* lpHandles);

};
