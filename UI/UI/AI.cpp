#include "AI.h"
#include "BoardForm.h"
#include "../../Board.h"


AI::AI(Piece::Color color, BoardForm^ boardForm) : m_boardForm(boardForm), myColor(color), board(boardForm->getBoard())
{
}

void AI::play()
{
	// Get possible jumps
	auto jumps = board.jumps_by_color(myColor);
	if (jumps.size() > 0)
	{
		Random^ r = gcnew Random();
		int j = r->Next(jumps.size() - 1);
		Board::TreeNodePtr nodePtr = jumps[j];
		Piece* piece = nodePtr->pos->piece;
		bool crowned = false;
		do {
			uint8_t i = 0;
			for (; i < 4; i++)
			{
				if (nodePtr->jumps[i] != nullptr)
				{
					m_boardForm->jumpPiece(System::Drawing::Point(nodePtr->pos->pos.x, nodePtr->pos->pos.y), nodePtr->jumps[i]);
					bool crowned = m_boardForm->crownIfNeeded(nodePtr->jumps[i]->pos->pos.x, nodePtr->jumps[i]->pos->pos.y);
					break;
				}
			}

			nodePtr = board.possible_jumps(piece, 1);
		} while ((!crowned) && (nodePtr->jumps[Node::TOP_LEFT] || nodePtr->jumps[Node::TOP_RIGHT] || 
			     nodePtr->jumps[Node::BOTTOM_LEFT] || nodePtr->jumps[Node::BOTTOM_RIGHT]));
	}
	else
	{
		// No jumps to make. Lets try to make a move
		auto moves = board.moves_by_color(myColor);
		if (moves.size() > 0)
		{
			Random^ r = gcnew Random();
			int j = r->Next(moves.size() - 1);
			Board::TreeNodePtr nodePtr = moves[j];
			for (uint8_t i = 0; i < 4; i++)
			{
				if (nodePtr->jumps[i] != nullptr)
				{
					m_boardForm->movePiece(System::Drawing::Point(nodePtr->pos->pos.x, nodePtr->pos->pos.y),
										System::Drawing::Point(nodePtr->jumps[i]->pos->pos.x, nodePtr->jumps[i]->pos->pos.y));
					m_boardForm->crownIfNeeded(nodePtr->jumps[i]->pos->pos.x, nodePtr->jumps[i]->pos->pos.y);
					break;
				}
			}
		}
	}
	m_boardForm->play();
}
