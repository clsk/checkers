#pragma once
#include "../../Piece.h"
#include "../../Board.h"
#include "IEnemy.h"
namespace UI
{
	ref class BoardForm;
}
using namespace UI;
ref class AI : IEnemy
{
public:
	AI(Piece::Color color, BoardForm^ boardForm);
	virtual void play();
	virtual ~AI() {}

protected:
	BoardForm^ m_boardForm;
	Piece::Color myColor;
	Board& board;
};

