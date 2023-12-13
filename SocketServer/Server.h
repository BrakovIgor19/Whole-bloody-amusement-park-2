#pragma once

#include <functional>
#include "resource.h"
#include "framework.h"
#include "Channel.h"
#include "Session.h"
#include <pqxx/pqxx>
#include <set>

using pqxx::connection;
using pqxx::nontransaction;
using pqxx::work;
using pqxx::result;

using enum MessageTypes;


class Server
{
public:
	explicit Server();
	~Server();
	pair<size_t, shared_ptr<Session>> AddSession();

private:
	static inline size_t bufId = 1000-7;
	static inline CRITICAL_SECTION cs;
	unordered_map<size_t, shared_ptr<Session>> sessions;
	unordered_map<size_t, set<size_t>> onlineUsersInConv;
	void ProcessClient(SOCKET forwardSockOut, SOCKET forwardSockIn);
	void ProcessUpdateDataClient(size_t id, SOCKET forwardIn);
	// переделать на вариадическую функцию или не надо?
	//string getListUsersToString(vector<size_t> exceptions = {}, char separator = ';');
	string getAllConvAndActiveUserConv(size_t id, work& W, vector<size_t> exceptions);
	vector<string> SplitString(const string& str, string delimiter = ";");
	//size_t getEvent(DWORD nCount, const HANDLE* lpHandles);

	// Работа с базой данных
	//connection connectDB;
};
