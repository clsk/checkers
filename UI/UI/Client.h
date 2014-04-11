#pragma once
#include "Networker.h"

using System::String;

ref class Client : public Networker
{
public:
	Client(String^ _hostname, int _port) : hostname(_hostname), port(_port)
	{
	}

	bool connect();

private:
	String^ hostname;
	int port;
	TcpClient^ tcpClient;
};

