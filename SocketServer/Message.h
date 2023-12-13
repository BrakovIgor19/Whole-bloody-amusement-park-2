#pragma once


enum class MessageTypes : uint8_t
{
	MT_AUTHORIZATION,
	MT_AUTHORIZATION_FAILED,
	MT_AUTHORIZATION_SUCCESS,
	MT_EXIT,
	MT_GETDATA,
	MT_DATA,
	MT_USERS,
	MT_NODATA,
	MT_CONFIRM,
	MT_UPDATE_USER_LIST,
	MT_MESSAGE,
	MT_MESSAGE_ALL,
	MT_GET_ID_RECIPIENT
};


using enum MessageTypes;

//enum MessageRecipients
//{
//	MR_BROKER = 10,
//	MR_ALL = 50,
//	MR_USER = 100
//};

struct MessageHeader
{
	size_t to;		//int to;
	size_t from;	//int from;
	size_t type;	//int type;
	size_t size;	//int size;
};

class Message
{
	friend class BaseChannel;
	template<typename>
	friend class Channel;

public:
	explicit Message();
	Message(const Message&) = default;
	explicit Message(size_t to, size_t from, size_t type, const string& data);
	explicit Message(size_t to, size_t from, MessageTypes type, const string& data);
	explicit Message(MessageTypes type, const string& data);
	explicit Message(size_t from, MessageTypes type, const string& data);
	explicit Message(size_t to, const string& data);
	explicit Message(MessageTypes type);
	MessageHeader GetHeader();
	string GetDate();
private: 
	MessageHeader header; 
	string data;
	
};
