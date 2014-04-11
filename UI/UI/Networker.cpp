#include "Networker.h"

using System::Byte;
using System::IntPtr;
using namespace System::Windows::Forms;

Networker::Networker() : ubuffer(nullptr)
{
}

Networker::~Networker()
{
	if (ubuffer != nullptr)
		delete ubuffer;
}

void Networker::send(const move& message)
{
	if (writer != nullptr)
		writer->Write(toCLI(message.SerializeAsString()));
}

void Networker::checkMessage(Object^ myObject, System::EventArgs^ myEventArgs)
{

	if (clientSocket->Poll(5, SelectMode::SelectRead))
	{
		if (clientSocket->Connected)
		{
			int transferred = clientSocket->Receive(inbuffer);
			if (transferred > 0)
			{
				fromCLI(inbuffer, ubuffer, transferred);
				move m;
				m.ParseFromArray(ubuffer, transferred);
				notifyMove(m);
			}
		}
	}
}

array<Byte>^ Networker::toCLI(const std::string& str)
{
	array<Byte>^ data = gcnew array<Byte>(str.size());
	System::Runtime::InteropServices::Marshal::Copy(IntPtr((void*)&str[0]), data, 0, str.size());

	return data;
}

void Networker::fromCLI(array<unsigned char>^ src, char* dest, int len)
{
	System::Runtime::InteropServices::Marshal::Copy(src, 0, IntPtr((void*)dest), len);
}