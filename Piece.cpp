#include "Piece.h"

#include "Board.h"

std::uint8_t Piece::get_direction()
{
    if (color == Red)
        return DIRECTION_DOWN;
    else
        return DIRECTION_UP;
}