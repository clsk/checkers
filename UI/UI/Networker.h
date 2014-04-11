#pragma once
#include "INet.h"

using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

ref class Networker : INet
{
public:
	Networker();
	virtual ~Networker();
	virtual void send(const move& message);
	virtual void checkMessage(Object^ myObject, System::EventArgs^ myEventArgs);
	delegate void NotifyMove(const move&);
	delegate void Connected();
	NotifyMove^ notifyMove;
	Connected^ connected;

protected:
	virtual property Socket^ clientSocket
	{
		void set(Socket^ socket)
		{
			m_clientSocket = socket;
			NetworkStream^ netStream = gcnew NetworkStream(clientSocket);
			writer = gcnew BinaryWriter(netStream);
			inbuffer = gcnew array<unsigned char>(2048);
			ubuffer = new char[2048];
			receiveTimer = gcnew System::Windows::Forms::Timer();
			receiveTimer->Interval = 500;
			receiveTimer->Tick += gcnew System::EventHandler(this, &Networker::checkMessage);
			receiveTimer->Start();		
			connected();
		}

		Socket^ get()
		{
			return m_clientSocket;
		}
	};
	Socket^ m_clientSocket;
	BinaryWriter^ writer;
	array<unsigned char>^ inbuffer;
	char *ubuffer; // unmanaged buffer
	System::Windows::Forms::Timer^ receiveTimer;
	array<System::Byte>^ toCLI(const std::string& str);
	void fromCLI(array<unsigned char>^ src, char* dest, int len);
};

