// TranspFuncs.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "TranspFuncs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma comment(lib, "TranspFuncs.lib")
//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CTranspFuncsApp

BEGIN_MESSAGE_MAP(CTranspFuncsApp, CWinApp)
END_MESSAGE_MAP()


// Создание CTranspFuncsApp

CTranspFuncsApp::CTranspFuncsApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}




// Единственный объект CTranspFuncsApp

CTranspFuncsApp theApp;


// Инициализация CTranspFuncsApp

BOOL CTranspFuncsApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxSocketInit();

	return TRUE;
}

CTranspFuncsApp::~CTranspFuncsApp()
{

}

Pipe::Pipe()
{
	sServer.Create(1000-7);
	sServer.Listen();
	sServer.Accept(sServerClient);
}

void Pipe::JoinPipe()
{
	::sClient.Create();
	::sClient.Connect("127.0.0.1", 1000-7);
}

size_t Pipe::getConfirm(CSocket& s)
{
	return ReadFromPipe<size_t>(s);
}

void Pipe::LeavePipe()
{
	::sClient.Close();
}

Pipe::~Pipe()
{
	sServer.Close();
	sServerClient.Close();
}


void Pipe::SendCommand(const string& nameClient, Command command, CSocket& s)
{
	WriteToPipe<string>(nameClient, s);

	WriteToPipe<Command>(command, s);
}

void Pipe::SendSize_t(size_t sz_t, CSocket& s)
{
	WriteToPipe<size_t>(sz_t, s);
}

size_t Pipe::getSize_t()
{
	return ReadFromPipe<size_t>(sServerClient);
}

void Pipe::SendString(const string& str, CSocket& s)
{
	WriteToPipe<string>(str, s);
}

string Pipe::getString()
{
	return ReadFromPipe<string>(sServerClient);
}

char* Pipe::getUpdateInfo(char* updateInfo, CSocket& s)
{
	string bufStr = ReadFromPipe<string>(s);
	strcpy(updateInfo, bufStr.c_str());
	return updateInfo;
}

bool Pipe::CheckThreads(size_t numberThread)
{
	bool stop = false;
	string strBuf = string(3000, '\0');
	strBuf = string(getUpdateInfo(const_cast<char*>(strBuf.c_str()), ::sClient));
	strBuf.push_back('|');
	{
		int i = 0;
		int j = 0;
		for (; i < strBuf.size(); ++i)
		{
			if (strBuf[i] == '|')
			{
				if (stoi(strBuf.substr(j, i - j)) == numberThread)
				{
					stop = true;
					break;
				}
				j = i + 1;
			}
		}
	}

	return stop;
}

void Pipe::SendUpdateInfo(const string& updateInfo)
{
	WriteToPipe<string>(updateInfo, sServerClient);
}

char* __stdcall SendConnectionRequest(const char* nameClient, char* updateInfo)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();
	
	Pipe::SendCommand(string(nameClient), Command::Connection, ::sClient);

	Pipe::getUpdateInfo(updateInfo, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

	return updateInfo;
}

void __stdcall SendDisconnectRequest(const char* nameClient)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::DisconnectingConnection, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

}

void __stdcall StartThread(const char* nameClient)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::Start, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();
}

bool __stdcall StopThread(const char* nameClient, int numberThread)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::Stop, ::sClient);

	bool stop = Pipe::CheckThreads(numberThread);
	
	if (stop)
	{
		Pipe::SendSize_t(numberThread, ::sClient);
		
	}
	else
	{
		Pipe::SendSize_t(0, ::sClient);
	}

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

	return stop;
}

void __stdcall StopAllThreads(const char* nameClient)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::StopAll, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();
}

char* __stdcall Update(const char* nameClient, char* updateInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::UpdateInfo, ::sClient);
	
	Pipe::getUpdateInfo(updateInfo, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

	return updateInfo;
}

bool __stdcall SendSMS(const char* nameClient, int numberThread, const char* message)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::Send, ::sClient);

	bool send = Pipe::CheckThreads(numberThread);

	if (send)
	{
		Pipe::SendSize_t(numberThread, ::sClient);
		Pipe::SendString(string(message), ::sClient);
	}
	else
	{
		Pipe::SendSize_t(0, ::sClient);
	}

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

	return send;
}

void __stdcall SendSMSToServer(const char* nameClient, const char* message)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::SendMessageServer, ::sClient);

	Pipe::SendString(string(message), ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

}

void __stdcall SendSMSAll(const char* nameClient, const char* message)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(string(nameClient), Command::SendAll, ::sClient);

	Pipe::SendString(string(message), ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();

}

void __stdcall PlayProcess(const char* name, const char* title)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpTitle = const_cast<LPSTR>(title);

	CreateProcess(NULL, (LPSTR)name, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void __stdcall CloseServer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Pipe::JoinPipe();

	Pipe::SendCommand(" ", Command::CloseDialogue, ::sClient);

	Pipe::getConfirm(::sClient);

	Pipe::LeavePipe();
}

void Pipe::ReceiveConnectionRequest(const string& updateInfo)
{
	SendUpdateInfo(updateInfo);
}

Command Pipe::ReceiveCommand(string& nameClient)
{
	nameClient = getString();

	Command commandBuf = ReadFromPipe<Command>(sServerClient);
		
	return commandBuf;
}

size_t Pipe::ReceiveNumberThread()
{
	return getSize_t();
}

string Pipe::ReceiveSMS()
{
	return getString();
}

void Pipe::SendConfirm()
{
	WriteToPipe<size_t>(size_t(0), sServerClient);
}








