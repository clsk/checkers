#include "Client.h"

bool Client::connect()
{
	try
	{
		tcpClient = gcnew TcpClient(hostname, port);
		clientSocket = tcpClient->Client;
	}
	catch (SocketException^ ex)
	{
		return false;
	}

	return true;
}