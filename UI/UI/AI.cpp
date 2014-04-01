#include "AI.h"
#include "BoardForm.h"
#include "../../Board.h"


AI::AI(Piece::Color color, BoardForm^ boardForm) : m_boardForm(boardForm), myColor(color)
{
}

void AI::play()
{
	// Get possible jumps
	auto jumps = Board::getInstance().jumps_by_color(myColor);
	if (jumps.size() > 0)
	{
		Random^ r = gcnew Random();
		r->Next(jumps.size() - 1);
	}
	else
	{

	}
}
