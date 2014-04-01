#ifndef _BOARD
#define _BOARD

#include "Piece.h"
#include <map>
#include <cstdint>
#include <utility>
#include <memory>
#include <vector>

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define PIECES_COUNT 12
#define BOARD_LIMIT 64

// struct Piece;
class MoveMemento;

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
		bool operator()(const ::Point& _Left, const ::Point& _Right) const
		{	// apply operator< to operands
			if (_Left.x != _Right.x)
				return (_Left.x < _Right.x);
			else
				return (_Left.y < _Right.y);
		}
};

struct Node
{
	Node() { piece = nullptr; memset(adjacents, 0, 4); }
	::Point pos;
	Piece *piece; // null if no piece present
	static const uint8_t BOTTOM_LEFT = 0, BOTTOM_RIGHT = 1, TOP_LEFT = 2, TOP_RIGHT = 3;
	Node *adjacents[4];
};

struct TreeNode
{
    Node *pos;
    Node *killed;
	std::shared_ptr<TreeNode> jumps[4];
};

class Board
{
public:
    typedef std::shared_ptr<::TreeNode> TreeNodePtr;
	typedef std::map<::Point, Node*, PointCompare> NodesType;

	Node* get_node(const ::Point& point);
	Piece* get_piece(const ::Point& point);

	void crown_piece(Piece* piece);
	void crown_piece(const ::Point& point); 

    void move_piece(Piece* piece, Node* from, Node* to);
    bool move_piece(const ::Point& from, const ::Point& to);	

	void remove_piece(const ::Point& location);
	void remove_piece(Piece* piece);

    void print();

    MoveMemento get_memento();
	TreeNodePtr possible_moves(Piece* piece);
	std::vector<TreeNodePtr> moves_by_color(Piece::Color color);

    TreeNodePtr possible_jumps(Piece* piece, uint8_t depth = -1);
	std::vector<TreeNodePtr> jumps_by_color(Piece::Color color, uint8_t depth = 1);
	void create_pieces();
	static Board& getInstance()
	{
		if (instance == nullptr)
			instance = new Board();

		return *instance;
	}

	Piece *red_pieces[PIECES_COUNT];
	Piece *black_pieces[PIECES_COUNT];
private:
	Board();
    TreeNodePtr build_tree_node(Node* pos, Node* killed = nullptr);
	TreeNodePtr discover_move(TreeNodePtr node, uint8_t direction);
	bool discover_jump(TreeNodePtr tree_node, Piece::Color color, uint8_t direction, uint8_t depth);
	void discover_jumps(TreeNodePtr tree_node, Piece::Color color, bool is_king, uint8_t depth);
	void link_adjacent_nodes(Node* node);
	NodesType nodes;	
	static Board * instance;
};

#endif
