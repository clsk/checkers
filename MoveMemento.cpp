//
//  MoveMemento.cpp
//  checkers
//
//  Created by Alan Alvarez on 3/8/14.
//  Copyright (c) 2014 Alan Alvarez. All rights reserved.
//

#include "Board.h"
#include "MoveMemento.h"

#include <iostream>

using namespace std;

MoveMemento::MoveMemento(Board& _board, bool _scoped) : board(_board), moves(), scoped(_scoped)
{
}

MoveMemento::~MoveMemento()
{
	if (scoped)
		rollback();
}

bool MoveMemento::move(const Point& from, const Point& to)
{
    Node* from_node = board.get_node(from);
    if (from_node == nullptr)
        return false;

    Node* to_node = board.get_node(to);
    if (to_node == nullptr)
        return false;

	return move(from_node, to_node);
}

bool MoveMemento::move(Node* from, Node* to)
{
    Piece *piece = from->piece;

    board.move_piece(piece, from, to);
	bool crowned = (piece->is_king == false && (to->pos.y == 0 || to->pos.y == 7));
	if (crowned)
	{
		piece->is_king = true;
	}
    MMove move(piece, from, to, crowned);
    moves.push(move);

	return crowned;
}

void MoveMemento::remove_piece(Piece* piece)
{
	piece->location->piece = nullptr;
	if (piece->color == Piece::Color::Red)
		board.red_pieces[piece->index] = nullptr;
	else
		board.black_pieces[piece->index] = nullptr;
}

void MoveMemento::unremove_piece(Piece* piece, Node* location)
{
	location->piece = piece;
	if (piece->color == Piece::Color::Red)
		board.red_pieces[piece->index] = piece;
	else
		board.black_pieces[piece->index] = piece;
}

bool MoveMemento::jump(Node* from, Node* to, Piece* killed)
{
	Piece* piece = from->piece;
	board.move_piece(piece, from, to);
	bool crowned = (piece->is_king == false && (to->pos.y == 0 || to->pos.y == 7));
	if (crowned)
	{
		piece->is_king = true;
	}
	MMove move(piece, from, to, crowned, killed, killed->location);
	moves.push(move);
	remove_piece(killed);

	return crowned;
}

inline unsigned short MoveMemento::rollback()
{
    return rollback(moves.size());
}

unsigned short MoveMemento::rollback(unsigned short n)
{
    unsigned short i = 0;
    for (; i < n && moves.size() > 0; i++)
    {
        const MMove& move = moves.top();
        moves.pop();
        board.move_piece(move.piece, move.to, move.from);
		if (move.killed != nullptr)
			unremove_piece(move.killed, move.killed_pos);
		if (move.crowned)
			move.piece->is_king = false;
    }
    
    return i;
}

bool MoveMemento::make_longest_jump(Board::TreeNodePtr start)
{
		bool crowned = false;
		for (Board::TreeNodePtr nextJump = start->jumps[start->longest_jump], previousJump = start; !crowned && nextJump != nullptr; 
			previousJump = nextJump, nextJump = nextJump->longest_jump != UINT8_MAX ? nextJump->jumps[nextJump->longest_jump] : nullptr)
		{
			crowned = jump(previousJump->pos,  nextJump->pos, nextJump->killed->piece);
		}

		return crowned;
}