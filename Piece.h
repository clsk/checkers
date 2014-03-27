#ifndef _PIECE
#define _PIECE
#include <cstdint>
struct Node; // Forward Declaration

struct Piece
{
    enum Color
	{
		Red,
		Black
	};
    
    std::uint8_t get_direction();

	Color color;
	bool is_king;
	Node *location;
};

#endif
