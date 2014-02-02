#ifndef _PIECE
#define _PIECE
struct Node; // Forward Declaration

struct Piece
{
    enum Color
	{
		Red,
		Black
	};

	Color color;
	bool is_king;
	Node *location;
};

#endif
