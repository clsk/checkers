#pragma once
#include "../../Piece.h"
namespace UI
{
	ref class BoardForm;
}
using namespace UI;
ref class AI
{
public:
	AI(Piece::Color color, BoardForm^ boardForm);
	void play();
	virtual ~AI() {}

private:
	BoardForm^ m_boardForm;
	Piece::Color myColor;
};

