#include "NetOponent.h"

#include "Networker.h"
#include "BoardForm.h"

using namespace UI;

NetOponent::NetOponent(Networker^ _net, BoardForm^ _boardForm) : net(_net), boardForm(_boardForm)
{
	net->notifyMove = gcnew Networker::NotifyMove(this, &NetOponent::PerformMove);
	net->connected = gcnew Networker::Connected(this, &NetOponent::HandleConnected);
}


NetOponent::~NetOponent()
{
}

void NetOponent::play()
{
	for (const move& m : *boardForm->moves)
	{
		net->send(m);
	}
}

inline void NetOponent::PerformMove(const move& m)
{
	Board& board = boardForm->getBoard();
	Node* to = board.get_node(::Point(m.to().x(), m.to().y()));
	if (m.has_killed())
	{
		Node* killed = boardForm->getBoard().get_node(::Point(m.killed().x(), m.killed().y()));
		Board::TreeNodePtr t = board.build_tree_node(to, killed);
		boardForm->jumpPiece(System::Drawing::Point(m.from().x(), m.from().y()), t);
	}
	else
	{
		boardForm->movePiece(System::Drawing::Point(m.from().x(), m.from().y()), System::Drawing::Point(m.to().x(), m.to().y()));
	}

	if (m.finished())
	{
		boardForm->crownIfNeeded(m.to().x(), m.to().y());
		boardForm->play();
	}
}

void NetOponent::HandleConnected()
{
	if (boardForm->myColor == Piece::Red)
		boardForm->play();
}