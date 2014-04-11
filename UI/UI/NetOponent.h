#pragma once
#include "IEnemy.h"

ref class Networker;
class move;
namespace UI
{
	ref class BoardForm;
}

using namespace System::Net;
using namespace System::Net::PeerToPeer;
using namespace System::Net::PeerToPeer::Collaboration;

ref class NetOponent : public IEnemy
{
public:
	NetOponent(Networker^ net, UI::BoardForm^ boardForm);
	virtual ~NetOponent();
	virtual void play();
	void PerformMove(const move& m);
	void HandleConnected();
private:
	Networker^ net;
	UI::BoardForm^ boardForm;
};
