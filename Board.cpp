#include "Board.h"
#include "Piece.h"
#include "MoveMemento.h"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;



MoveMemento Board::get_memento()
{
    return MoveMemento(*this);
}

void Board::link_adjacent_nodes(Node* node)
{

	// BOTTOM_LEFT
	Point pos = node->pos;
	if ((pos.x) > 0 && (pos.y) > 0) {
		node->adjacents[Node::BOTTOM_LEFT] = get_node(Point(pos.x-1, pos.y-1));
	}
	else
	{
		node->adjacents[Node::BOTTOM_LEFT] = nullptr;
	}

	// BOTTOM_RIGHT
	if ((pos.x+1) < 8 && (pos.y) > 0) {
		node->adjacents[Node::BOTTOM_RIGHT] = get_node(Point(pos.x+1, pos.y-1));
	}
	else
	{
		node->adjacents[Node::BOTTOM_RIGHT] = nullptr;
	}

	// TOP_LEFT
	if ((pos.x) > 0 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_LEFT] = get_node(Point(pos.x-1, pos.y+1));
	}
	else
	{
		node->adjacents[Node::TOP_LEFT] = nullptr;
	}

	// TOP_RIGHT
	if ((pos.x+1) < 8 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_RIGHT] = get_node(Point(pos.x+1, pos.y+1));
	}
	else
	{
		node->adjacents[Node::TOP_RIGHT] = nullptr;
	}
}

Board::Board()
{
	// Create nodes
	// int i = 1;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x+= 2) {
			Node *node = new Node;
            node->pos.x = (y%2 == 0) ? x : x+1;
			node->pos.y = y;
			nodes.insert(NodesType::value_type(node->pos, node));
			// cout << i << " - Creating node (" << node->pos.x << "," << node->pos.y << ")" << endl;
			// i++;
		}
	}

	// Link nodes
	for (NodesType::iterator Iter = nodes.begin(); Iter != nodes.end(); ++Iter) {
		link_adjacent_nodes(Iter->second);
	}
}

Node* Board::get_node(const Point& pos)
{
	NodesType::iterator Iter = nodes.find(pos);
	if (Iter != nodes.end())
		return Iter->second;
	else
		return nullptr;
}

Piece* Board::get_piece(const Point& point)
{
	Node* node = get_node(point);
	if (node != nullptr)
		return node->piece;

	return nullptr;
}

void Board::move_piece(Piece* piece, Node* from, Node* to)
{
    from->piece = nullptr;
    to->piece = piece;
    piece->location = to;
}

bool Board::move_piece(const Point& from, const Point& to)
{
    Node* from_node = get_node(from);
    if (from_node == nullptr)
        return false;

    Node* to_node = get_node(to);
    if (to_node == nullptr)
        return false;

    Piece *piece = from_node->piece;
    if (piece == nullptr)
        return false;

    move_piece(piece, from_node, to_node);

    return true;
}
void Board::remove_piece(const Point& location)
{
	remove_piece(get_piece(location));
}
void Board::remove_piece(Piece* piece)
{
	if (piece != nullptr)
	{
		piece->location->piece = nullptr;
		piece->location = nullptr;
		delete piece;
	}
}

void Board::crown_piece(Piece* piece)
{
	if (piece != nullptr)
		piece->is_king = true;
}

void Board::crown_piece(const Point& point)
{
	crown_piece(get_piece(point));
}

void Board::print()
{
    cout << "   0   1   2   3   4   5   6   7" << endl;
    for (int y = 0; y < 8; y++) {
        cout << y;
        for (int x = 0; x < 8; x += 2) {
            bool odd = bool(y%2);
            Point point;
            if (odd) {
                point.x = x+1;
                cout << "|   ";
            } else {
                point.x = x;
            }
            Piece* piece = get_node(Point( (odd) ? x+1 : x,y))->piece;
            if (piece == nullptr)
                cout << "|   ";
            else if (piece->color == Piece::Red) {
                cout << "| " << (piece->is_king ? "R " : "r ");
            } else if (piece->color == Piece::Black) {
                cout << "| " << (piece->is_king ? "B " : "b ");
            }

            if (!odd) {
                cout << "|   ";
            }
        }
        cout << "|" << y << endl;
        cout << "  --- --- --- --- --- --- --- ---" << endl;
    }
    cout << "   0   1   2   3   4   5   6   7" << endl;
}

void Board::create_pieces()
{
	// Black Pieces
	int i = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 8; x+= 2) {
			Piece *piece = new Piece;
			piece->color = Piece::Black;
			piece->is_king = false;
			Point pos;
			pos.y = y;
			if (y % 2 == 0)
				pos.x = x;
			else
				pos.x = x+1;

			Node *node = get_node(Point(pos.x,pos.y));
			piece->location = node;
			node->piece = piece;
			black_pieces[i] = piece;
			//cout << i << " - Creating black piece at (" << pos.x << "," << pos.y << ")" << endl;
			i++;
		}
	}

	// Red Pieces
	i = 0;
	for (int y = 7; y > 4; y--) {
		for (int x = 0; x < 8; x+= 2) {
			Piece *piece = new Piece;
			piece->color = Piece::Red;
			piece->is_king = false;
			Point pos;
			pos.y = y;
			if (y % 2 == 0)
				pos.x = x;
			else
				pos.x = x+1;

			Node *node = get_node(Point(pos.x,pos.y));
			piece->location = node;
			node->piece = piece;
			red_pieces[i] = piece;
			//cout << i << " - Creating red piece at (" << pos.x << "," << pos.y << ")" << endl;
			i++;
		}
	}
}

Board::NodePair Board::possible_moves(Piece* piece, uint8_t direction)
{
	Node* node = piece->location;

	int left, right;
	if (direction == DIRECTION_DOWN) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
	}

	NodePair moves;
	moves.first = moves.second = nullptr;
	// Left
	if (node->adjacents[left] != nullptr && node->adjacents[left]->piece == nullptr)
		moves.first = node->adjacents[left];
	
	//Right
	if (node->adjacents[right] != nullptr && node->adjacents[right]->piece == nullptr)
		moves.second = node->adjacents[right];

	return moves;
}

std::pair<Board::NodePair, Board::NodePair> Board::possible_moves(Piece* piece)
{
	uint8_t dir, odir; // direction and opposite direction
	if (piece->color == Piece::Color::Red)
	{
		dir = DIRECTION_DOWN;
		odir = DIRECTION_UP;
	}
	else
	{
		dir = DIRECTION_UP;
		odir = DIRECTION_DOWN;
	}

	std::pair<NodePair, NodePair> moves;
	moves.first = possible_moves(piece, dir);
	if (piece->is_king)
		moves.second = possible_moves(piece, odir);
	else
		moves.second.first = moves.second.second = nullptr;

	return moves;
}

Board::TreeNodePtr Board::build_tree_node(Node* pos, Node* killed)
{
	auto tree_node = make_shared<TreeNode>();
	tree_node->pos = pos;
	tree_node->killed = killed;
	return tree_node;
}

Board::TreeNodePtr Board::possible_jumps(Piece* piece, uint8_t depth)
{
	// Build possible jumps
	auto start = build_tree_node(piece->location);
	discover_jumps(start, piece->color, depth);

	return start;
}

void Board::print_possible_jumps(TreeNodePtr start)
{
    if (start != nullptr)
    {
        cout << "(" << start->pos->pos.x << "," << start->pos->pos.y << "): ";
    }
    
    if (start->left != nullptr)
    {
        cout << "(left)" << "(" << start->left->pos->pos.x << "," << start->left->pos->pos.y << ")";
        print_possible_jumps(start->left);
    }
    
    if (start->right != nullptr)
    {
        cout << "(right)" << "(" << start->right->pos->pos.x << "," << start->right->pos->pos.y << ")";
        print_possible_jumps(start->right);
    }
    
    cout << endl;
}

void Board::print_possible_jumps(Piece* piece)
{
    print_possible_jumps(possible_jumps(piece));
}

void Board::discover_jumps(TreeNodePtr tree_node, Piece::Color color, uint8_t depth)
{
	if (depth == 0 || tree_node == nullptr)
		return;
    
	int left, right;
	if (color == Piece::Red) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
	}

	Node* left_tree_node = nullptr;
	Node* right_tree_node = nullptr;
	--depth; // Decrease depth here, for recursive call
	left_tree_node = tree_node->pos->adjacents[left];
	if (left_tree_node != nullptr && left_tree_node->piece != nullptr && left_tree_node->piece->color != color) {
		// We have a piece, check for emptiness left
		if (left_tree_node->adjacents[left] != nullptr && left_tree_node->adjacents[left]->piece == nullptr) {
			tree_node->left = build_tree_node(left_tree_node->adjacents[left], left_tree_node);
			discover_jumps(tree_node->left, color, depth);
		}
	}

	right_tree_node = tree_node->pos->adjacents[right] != nullptr ? tree_node->pos->adjacents[right] : nullptr;
	if (right_tree_node != nullptr && right_tree_node->piece != nullptr && right_tree_node->piece->color != color) {
		// We have a piece, check for emptiness right
		if (right_tree_node->adjacents[right] != nullptr && right_tree_node->adjacents[right]->piece == nullptr) {
			tree_node->right = build_tree_node(right_tree_node->adjacents[right], right_tree_node);
			discover_jumps(tree_node->right, color, depth);
		}
	}
}

Board* Board::instance = nullptr;