#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <memory>

#include "Game.h"
// #include "Piece.h"

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::shared_ptr;
using std::make_shared;

void Game::create_pieces()
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

			Node *node = Game::instance().get_board().get_node(Point(pos.x,pos.y));
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

			Node *node = Game::instance().get_board().get_node(Point(pos.x,pos.y));
			piece->location = node;
			node->piece = piece;
			red_pieces[i] = piece;
			//cout << i << " - Creating red piece at (" << pos.x << "," << pos.y << ")" << endl;
			i++;
		}
	}
}


std::pair<Node*,Node*> Game::possible_moves(Piece* piece)
{
	Node* node = piece->location;

	int left, right;
	if (piece->color == Piece::Red) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
	}

	std::pair<Node*, Node*> p;
	p.first = p.second = nullptr;
	// Left
	if (node->adjacents[left]->piece == nullptr)
		p.first = node->adjacents[left];
	
	//Right
	if (node->adjacents[right]->piece == nullptr)
		p.second = node->adjacents[right];

	return p;
}

Game::TreeNodePtr Game::build_tree_node(Node* pos, Node* killed)
{
	auto tree_node = make_shared<TreeNode>();
	tree_node->pos = pos;
	return tree_node;
}

Game::TreeNodePtr Game::possible_jumps(Piece* piece, uint8_t depth)
{
	// Build possible jumps
	auto start = build_tree_node(piece->location);
	discover_jumps(start, piece->get_direction(), depth);

	return start;
}

void Game::print_possible_jumps(TreeNodePtr start)
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

void Game::print_possible_jumps(Piece* piece)
{
    print_possible_jumps(possible_jumps(piece));
}

void Game::discover_jumps(TreeNodePtr tree_node, uint8_t direction, uint8_t depth)
{
	if (depth == 0 || tree_node == nullptr)
		return;
    
	int left, right;
	if (direction == DIRECTION_DOWN) {
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
	if (left_tree_node != nullptr && left_tree_node->piece != nullptr) {
		// We have a piece, check for emptiness left
		if (left_tree_node->adjacents[left] != nullptr && left_tree_node->adjacents[left]->piece == nullptr) {
			tree_node->left = build_tree_node(left_tree_node->adjacents[left], left_tree_node);
			discover_jumps(tree_node->left, direction, depth);
		}
	}

	right_tree_node = tree_node->pos->adjacents[right];
	if (right_tree_node != nullptr && right_tree_node->piece != nullptr) {
		// We have a piece, check for emptiness right
		if (right_tree_node->adjacents[right] != nullptr && right_tree_node->adjacents[right]->piece == nullptr) {
			tree_node->right = build_tree_node(right_tree_node->adjacents[right], right_tree_node);
			discover_jumps(tree_node->right, direction, depth);
		}
	}
}


Game *Game::m_instance;
