#include <vector>
#include <list>
#include <set>
#include <iostream>

#include "Game.h"
// #include "Piece.h"

using std::cout;
using std::endl;
using std::vector;
using std::list;

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


void Game::possible_moves(Piece* piece, vector<Node*> &nodes)
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

	// Left
	if (node->adjacents[left]->piece == NULL)
		nodes.push_back(node->adjacents[left]);
	//Right
	if (node->adjacents[right]->piece == NULL)
		nodes.push_back(node->adjacents[right]);
}

void Game::possible_moves_by_color(Piece::Color color, std::vector<Node*> &nodes)
{
	for (int i = 0; i < PIECES_COUNT; ++i) {
		possible_moves(red_pieces[i], nodes);
	}
}

std::vector<std::list<Node*> > Game::possible_jumps(Piece* piece)
{
	vector<list<Node*> > paths;
	// Build possible jumps
	TreeNode* start = build_empty_tree_node(piece->location);
	discover_jumps(start, piece->color == Piece::Red ? DIR_DOWN : DIR_UP);


	return paths;
}

#define DIR_UP 0
#define DIR_DOWN 1

TreeNode* Game::build_filled_tree_node(Node* pos)
{
	TreeNode *tree_node = new TreeNode;
	tree_node->pos = pos;
	tree_node->space = 1; // filled
	return tree_node;
}

TreeNode* Game::build_empty_tree_node(Node* pos)
{
	TreeNode* tree_node = new TreeNode;
	tree_node->pos = pos;
	tree_node->space = 0;
	return tree_node;
}

void Game::discover_jumps(TreeNode *tree_node, int direction)
{
	if (tree_node == NULL)
		return;

	int left, right;
	if (direction == DIR_DOWN) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
	}

	TreeNode *left_tree_node = NULL;
	TreeNode *right_tree_node = NULL;
	if (tree_node->pos->adjacents[left] != NULL && tree_node->pos->adjacents[left]->piece != NULL) {
		left_tree_node = build_filled_tree_node(tree_node->pos->adjacents[left]);
		// We have a piece, check for emptiness left and right
		if (left_tree_node->pos->adjacents[left] != NULL && left_tree_node->pos->adjacents[left]->piece == NULL) {
			left_tree_node->left = build_empty_tree_node(left_tree_node->pos->adjacents[left]);
			discover_jumps(left_tree_node->left, direction);
		}
		if (left_tree_node->pos->adjacents[right] != NULL && left_tree_node->pos->adjacents[right]->piece == NULL) {
			left_tree_node->right = build_empty_tree_node(left_tree_node->pos->adjacents[right]);
			discover_jumps(left_tree_node->right, direction);
		}

		// Only attach if there is a kill to make
		if (left_tree_node->left != NULL || left_tree_node->right != NULL)
			tree_node->right = left_tree_node;
	}

	if (tree_node->pos->adjacents[right] != NULL && tree_node->pos->adjacents[right]->piece != NULL) {
		right_tree_node = build_filled_tree_node(tree_node->pos->adjacents[left]);
		// We have a piece, check for emptiness left and right
		if (right_tree_node->pos->adjacents[left] != NULL && right_tree_node->pos->adjacents[left]->piece == NULL) {
			right_tree_node->left = build_empty_tree_node(right_tree_node->pos->adjacents[left]);
			discover_jumps(right_tree_node->left, direction);
		}
		if (right_tree_node->pos->adjacents[right] != NULL && right_tree_node->pos->adjacents[right]->piece == NULL) {
			right_tree_node->right = build_empty_tree_node(right_tree_node->pos->adjacents[right]);
			discover_jumps(right_tree_node->right, direction);
		}

		// Only attach if there is a kill to make
		if (right_tree_node->left != NULL || right_tree_node->right != NULL)
			tree_node->right = right_tree_node;
	}
}


Game *Game::m_instance;
