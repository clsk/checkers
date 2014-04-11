#include "Server.h"
#include "Messages.pb.h"



void Server::start()
{
	listener = gcnew TcpListener(IPAddress::Any, port);
	listener->Start();
	listenTimer = gcnew System::Windows::Forms::Timer();
	listenTimer->Interval = 500;
	listenTimer->Tick += gcnew System::EventHandler(this, &Server::checkConnection);
	listenTimer->Start();
}



void Server::checkConnection(Object^ myObject, System::EventArgs^ myEventArgs)
{
	if (listener->Pending())
	{
		listenTimer->Stop();
		clientSocket = listener->AcceptSocket();
		listener->Stop();
	}
}

