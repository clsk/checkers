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

MoveMemento::MoveMemento(Board& _board) : board(_board), moves()
{
}

bool MoveMemento::move(const Point& from, const Point& to)
{
    Node* from_node = board.get_node(from);
    if (from_node == nullptr)
        return false;

    Node* to_node = board.get_node(to);
    if (to_node == nullptr)
        return false;

    Piece *piece = from_node->piece;
    if (piece == nullptr)
        return false;

    board.move_piece(piece, from_node, to_node);
    MoveType t = MoveType(piece, from_node, to_node);
    moves.push(t);
    
    return true;
}

unsigned short MoveMemento::rollback()
{
    return rollback(moves.size());
}

unsigned short MoveMemento::rollback(unsigned short n)
{
    unsigned short i = 0;
    for (; i < n && moves.size() > 0; i++)
    {
        const MoveType& move = moves.top();
        moves.pop();
        board.move_piece(get<0>(move), get<2>(move), get<1>(move));
    }
    
    return i;
}
