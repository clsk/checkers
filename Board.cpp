#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"
#include "Piece.h"
#include "Game.h"
#include "MoveMemento.h"

MoveMemento Board::get_memento()
{
    return MoveMemento(*this);
}

void Board::link_adjacent_nodes(Node* node)
{

	// BOTTOM_LEFT
	Point pos = node->pos;
	if ((pos.x) > 1 && (pos.y) > 1) {
		node->adjacents[Node::BOTTOM_LEFT] = get_node(Point(pos.x-1, pos.y-1));

		//printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x-1, pos.y-1);
	}

	// BOTTOM_RIGHT
	if ((pos.x+1) < 8 && (pos.y) > 1) {
		node->adjacents[Node::BOTTOM_RIGHT] = get_node(Point(pos.x+1, pos.y-1));

		//printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x+1, pos.y-1);
	}

	// TOP_LEFT
	if ((pos.x) > 1 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_LEFT] = get_node(Point(pos.x-1, pos.y+1));

		//printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x-1, pos.y+1);
	}

	// TOP_RIGHT
	if ((pos.x+1) < 8 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_RIGHT] = get_node(Point(pos.x+1, pos.y+1));
		//printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x+1, pos.y+1);
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
