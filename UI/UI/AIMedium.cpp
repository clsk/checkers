#include "AIMedium.h"
#include "BoardForm.h"

AIMedium::AIMedium(Piece::Color color, BoardForm^ boardForm) : AI(color, boardForm)
{
}

void AIMedium::play()
{
	auto jump = board.longest_jump_by_color(myColor);
	if (jump.first > 0)
	{
		bool crowned = false;
		for (Board::TreeNodePtr nextJump = jump.second->jumps[jump.second->longest_jump], previousJump = jump.second; !crowned && nextJump != nullptr; 
			previousJump = nextJump, nextJump = nextJump->longest_jump != UINT8_MAX ? nextJump->jumps[nextJump->longest_jump] : nullptr)
		{
			m_boardForm->jumpPiece(System::Drawing::Point(previousJump->pos->pos.x, previousJump->pos->pos.y), nextJump);
			crowned = m_boardForm->crownIfNeeded(nextJump->pos->pos.x, nextJump->pos->pos.y);
		}
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

AIMedium::~AIMedium()
{
}
