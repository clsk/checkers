#include "AIHard.h"
#include "BoardForm.h"
#include "../../MoveMemento.h"

#include <algorithm>

AIHard::AIHard(Piece::Color color, BoardForm^ boardForm, uint8_t depth) : AI(color, boardForm), m_depth(depth)
{
}

void AIHard::play()
{
	bool has_jumps = board.has_possible_jumps(myColor);
	Piece ** pieces = myColor == Piece::Color::Red ? board.red_pieces : board.black_pieces;
	Piece::Color min_color = myColor == Piece::Red ? Piece::Black : Piece::Red;
	MoveMemento memento = board.get_memento();
	int8_t best_value = INT8_MIN;
	Board::TreeNodePtr best_move = Board::TreeNodePtr(nullptr);
	uint8_t best_move_dir = UINT8_MAX;

	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		if (has_jumps)
		{
			// Assume longest jump
			std::pair<uint8_t, Board::TreeNodePtr> optimum_jump = board.longest_jump(pieces[i]);
			if (optimum_jump.first > 0)
			{
				memento.make_longest_jump(optimum_jump.second);
				int8_t value = board.minimax(memento, m_depth - 1, myColor, min_color, true);
				if (value > best_value)
				{
					best_value = value;
					best_move = optimum_jump.second;
				}
				memento.rollback(optimum_jump.first);
			}
		}
		else
		{
			// If player can't make any jumps, check for best move
			Board::TreeNodePtr moves = board.possible_moves(pieces[i]);
			for (uint8_t j = 0; j < 4; j++)
			{
				if (moves->jumps[j] != nullptr)
				{
					memento.move(moves->pos, moves->jumps[j]->pos);
					int8_t value = board.minimax(memento, m_depth - 1, myColor, min_color, true);
					if (value > best_value)
					{
						best_value = value;
						best_move = moves;
						best_move_dir = j;
					}
					memento.rollback(1);
				}
			}
		}
	}

	MessageBox::Show("Best value is: " + best_value);
	if (best_move != nullptr)
	{
		if (best_move->longest_jump == UINT8_MAX) // this is a simple move
		{
			m_boardForm->movePiece(System::Drawing::Point(best_move->pos->pos.x, best_move->pos->pos.y),
									 System::Drawing::Point(best_move->jumps[best_move_dir]->pos->pos.x, best_move->jumps[best_move_dir]->pos->pos.y));
			m_boardForm->crownIfNeeded(best_move->jumps[best_move_dir]->pos->pos.x, best_move->jumps[best_move_dir]->pos->pos.y);
		}
		else // this is a (longest) jump
		{
			bool crowned = false;
			for (Board::TreeNodePtr nextJump = best_move->jumps[best_move->longest_jump], previousJump = best_move; !crowned && nextJump != nullptr; 
				previousJump = nextJump, nextJump = nextJump->longest_jump != UINT8_MAX ? nextJump->jumps[nextJump->longest_jump] : nullptr)
			{
				m_boardForm->jumpPiece(System::Drawing::Point(previousJump->pos->pos.x, previousJump->pos->pos.y), nextJump);
				crowned = m_boardForm->crownIfNeeded(nextJump->pos->pos.x, nextJump->pos->pos.y);
			}
		}
	}

	m_boardForm->play();
}

AIHard::~AIHard()
{
}
