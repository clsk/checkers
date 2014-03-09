//
//  MoveMemento.cpp
//  checkers
//
//  Created by Alan Alvarez on 3/8/14.
//  Copyright (c) 2014 Alan Alvarez. All rights reserved.
//

#include "Board.h"
#include "MoveMemento.h"


MoveMemento::MoveMemento(Board& _board) : board(_board), moves()
{
}

bool MoveMemento::move(const Point& from, const Point& to)
{
    bool moved =  board.move_piece(from, to);
    if (moved)
        moves.push(std::make_pair(from, to));
    
    return moved;
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
        MoveType move = moves.top();
        board.move_piece(move.second, move.first);
    }
    
    return i;
}
