#include "pch.h"
#include "Session.h"



Session::Session(string firstName, string lastName) : firstName(firstName), lastName(lastName), isValid(true)
{
	//hEventUpdateDataClient = CreateEvent(NULL, TRUE, FALSE, string("UpdateEvent" + name).c_str());
	hEventUpdateDataClient = CreateEvent(
		NULL, // атрибуты защиты
		TRUE, // тип события
		FALSE, // начальное состояние события
		"EventUpdateDataClient" // имя события
	);
	hEventExit = CreateEvent(
		NULL, // атрибуты защиты
		FALSE, // тип события
		FALSE, // начальное состояние события
		"EventExit" // имя события
	);
}

Session::Session() : firstName("No firstname"), lastName("No lastname"), isValid(true)
{
	hEventUpdateDataClient = CreateEvent(
		NULL, // атрибуты защиты
		TRUE, // тип события
		FALSE, // начальное состояние события
		"EventUpdateDataClient" // имя события
	);
	hEventExit = CreateEvent(
		NULL, // атрибуты защиты
		FALSE, // тип события
		FALSE, // начальное состояние события
		"EventExit" // имя события
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
