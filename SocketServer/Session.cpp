#include "pch.h"
#include "Session.h"



Session::Session(string name) : name(name), isValid(true)
{
	//hEventUpdateDataClient = CreateEvent(NULL, TRUE, FALSE, string("UpdateEvent" + name).c_str());
	hEventUpdateDataClient = CreateEvent(
		NULL, // �������� ������
		TRUE, // ��� �������
		FALSE, // ��������� ��������� �������
		"EventUpdateDataClient" // ��� �������
	);
	hEventExit = CreateEvent(
		NULL, // �������� ������
		FALSE, // ��� �������
		FALSE, // ��������� ��������� �������
		"EventExit" // ��� �������
	);
}

Session::Session() : name("No name"), isValid(true)
{
	hEventUpdateDataClient = CreateEvent(
		NULL, // �������� ������
		TRUE, // ��� �������
		FALSE, // ��������� ��������� �������
		"EventUpdateDataClient" // ��� �������
	);
	hEventExit = CreateEvent(
		NULL, // �������� ������
		FALSE, // ��� �������
		FALSE, // ��������� ��������� �������
		"EventExit" // ��� �������
	);
}

void Session::AddMessageToQueue(const Message& m)
{
	messages.push(m);
}

Message Session::getMessage()
{
	Message bufMessage = messages.front();
	messages.pop();
	return bufMessage;
}
