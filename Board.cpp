#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"
#include "Game.h"

void Board::link_adjacent_nodes(Node* node)
{

	// BOTTOM_LEFT
	Point pos = node->pos;
	if ((pos.x) > 1 && (pos.y) > 1) {
		node->adjacents[Node::BOTTOM_LEFT] = get_node(Point(pos.x-1, pos.y-1));

		printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x-1, pos.y-1);
	}

	// BOTTOM_RIGHT
	if ((pos.x+1) < 8 && (pos.y) > 1) {
		node->adjacents[Node::BOTTOM_RIGHT] = get_node(Point(pos.x+1, pos.y-1));

		printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x+1, pos.y-1);
	}

	// TOP_LEFT
	if ((pos.x) > 1 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_LEFT] = get_node(Point(pos.x-1, pos.y+1));

		printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x-1, pos.y+1);
	}

	// TOP_RIGHT
	if ((pos.x+1) < 8 && (pos.y+1) < 8) {
		node->adjacents[Node::TOP_RIGHT] = get_node(Point(pos.x+1, pos.y+1));
		printf("Linking (%u,%u) with (%u,%u)\n", pos.x, pos.y, pos.x+1, pos.y+1);
	}
}

Board::Board()
{
	// Create nodes
	// int i = 1;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x+= 2) {
			Node *node = new Node;
			if (y % 2 == 0)
				node->pos.x = x;
			else
				node->pos.x = x+1;

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
		return NULL;
}

bool Board::move_piece(const Point& from, const Point& to)
{
    Node* from_node = get_node(from);
    if (from_node == NULL)
        return false;

    Node* to_node = get_node(to);
    if (to_node == NULL)
        return false;

    Piece *piece = from_node->piece;
    if (piece == NULL)
        return false;

    from_node->piece = NULL;
    to_node->piece = piece;
    piece->location = to_node;

    return true;
}

void Board::print()
{
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x += 2) {
            Piece* piece = get_node(Point( (y%2) ? x+1 : x,y))->piece;
            if (piece == NULL)
                cout << "|   ";
            else if (piece->color == Piece::Red) {
                cout << "| " << (piece->is_king ? "R " : "r ");
            } else if (piece->color == Piece::Black) {
                cout << "| " << (piece->is_king ? "B " : "b ");
            }
        }
        cout << "|" << endl;
    }
}
