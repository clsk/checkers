#ifndef _BOARD
#define _BOARD

#define BOARD_LIMIT 64
#include <map>

#include "Piece.h" 

using std::map;

struct Point
{
	Point(unsigned int _x, unsigned int _y)
	{
		x = _x;
		y = _y;
	}
	Point() {x=y=0;}
	unsigned int x,y;
};

struct PointCompare
{
		bool operator()(const Point& _Left, const Point& _Right) const
		{	// apply operator< to operands
			if (_Left.x != _Right.x)
				return (_Left.x < _Right.x);
			else
				return (_Left.y < _Right.y);
		}
};
struct Node
{
	Node() { piece = NULL; memset(adjacents, 0, 4); }
	Point pos;
	Piece *piece; // null if no piece present
	static const int BOTTOM_LEFT = 0, BOTTOM_RIGHT = 1, TOP_LEFT = 2, TOP_RIGHT = 3;
	Node *adjacents[4];
};

class Board
{
public:
	typedef map<Point, Node*, PointCompare> NodesType;
	Board();
	Node* get_node(const Point& point);
    bool move_piece(const Point& from, const Point& to);	
    void print();

private:
	void link_adjacent_nodes(Node* node);
	NodesType nodes;
};

#endif
