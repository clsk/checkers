#include "Piece.h"

#include "Board.h"

Direction Piece::get_direction()
{
    if (color == Red)
        return Direction::DOWN;
    else
        return Direction::UP;
}