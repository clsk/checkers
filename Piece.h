#ifndef _PIECE
#define _PIECE
#include <cstdint>
struct Node; // Forward Declaration
enum class Direction : std::uint8_t;

struct Piece
{
    enum Color
	{
		Red,
		Black
	};
    
    Direction get_direction();

	Color color;
	bool is_king;
	Node *location;
};

#endif
