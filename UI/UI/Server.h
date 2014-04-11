#pragma once
#include "Networker.h"

using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

ref class Server : public Networker
{
public:
	Server(int _port) : port(_port)
	{
	}
	void start();
	void checkConnection(Object^ myObject, System::EventArgs^ myEventArgs);

private:
	int port;
	TcpListener^ listener;
	System::Windows::Forms::Timer^ listenTimer;

};

