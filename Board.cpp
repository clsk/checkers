#include "Board.h"
#include "Piece.h"
#include "MoveMemento.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::max;



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

Board::~Board()
{
	// Delete Pieces
	for (int i = 0; i < PIECES_COUNT; i++)
	{
		if (red_pieces[i])
			delete red_pieces[i];

		if (black_pieces[i])
			delete black_pieces[i];
	}

	// Delete Nodes
	for (auto iter : nodes)
	{
		delete iter.second;
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

uint8_t Board::get_piece_count(Piece::Color color)
{
	Piece ** pieces = nullptr;
	if (color == Piece::Color::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	uint8_t count = 0;
	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] != nullptr)
			count++;
	}

	return count;
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
		if (piece->color == Piece::Color::Red)
			red_pieces[piece->index] = nullptr;
		else
			black_pieces[piece->index] = nullptr;
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
            bool odd = y%2 != 0;
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
			piece->index = i;
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
			piece->index = i;
			node->piece = piece;
			red_pieces[i] = piece;
			//cout << i << " - Creating red piece at (" << pos.x << "," << pos.y << ")" << endl;
			i++;
		}
	}
}

inline Board::TreeNodePtr Board::discover_move(TreeNodePtr tree_node, uint8_t direction)
{
	if (tree_node->pos != nullptr && tree_node->pos->adjacents[direction] != nullptr && tree_node->pos->adjacents[direction]->piece == nullptr)
		return build_tree_node(tree_node->pos->adjacents[direction], nullptr);

	return nullptr;
}

Board::TreeNodePtr Board::possible_moves(Piece* piece)
{
	uint8_t oleft, oright;
	TreeNodePtr root = build_tree_node(piece->location);
	if (piece->color == Piece::Color::Red)
	{
		root->jumps[Node::BOTTOM_LEFT] = discover_move(root, Node::BOTTOM_LEFT);
		root->jumps[Node::BOTTOM_RIGHT] = discover_move(root, Node::BOTTOM_RIGHT);

		oleft = Node::TOP_LEFT;
		oright = Node::TOP_RIGHT;
	}
	else
	{
		root->jumps[Node::TOP_LEFT] = discover_move(root, Node::TOP_LEFT);
		root->jumps[Node::TOP_RIGHT] = discover_move(root, Node::TOP_RIGHT);
		oleft = Node::BOTTOM_LEFT;
		oright = Node::BOTTOM_RIGHT;
	}

	if (piece->is_king)
	{
		root->jumps[oleft] = discover_move(root, oleft);
		root->jumps[oright] = discover_move(root, oright);
	}

	return root;
}


std::vector<Board::TreeNodePtr> Board::moves_by_color(Piece::Color color)
{
	Piece ** pieces = nullptr;
	if (color == Piece::Color::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	std::vector<TreeNodePtr> moves;
	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		TreeNodePtr treePtr = possible_moves(pieces[i]);
		if (treePtr->jumps[Node::TOP_LEFT] != nullptr || treePtr->jumps[Node::TOP_RIGHT] != nullptr ||
			treePtr->jumps[Node::BOTTOM_LEFT] != nullptr || treePtr->jumps[Node::BOTTOM_RIGHT] != nullptr)
			moves.push_back(treePtr);
	}

	return moves;
}

inline Board::TreeNodePtr Board::build_tree_node(Node* pos, Node* killed)
{
	auto tree_node = make_shared<TreeNode>();
	tree_node->pos = pos;
	tree_node->killed = killed;
	return tree_node;
}

Board::TreeNodePtr Board::possible_jumps(Piece* piece, uint8_t depth)
{
	// Build possible jumps
	TreeNodePtr start = build_tree_node(piece->location);
	discover_jumps(start, piece->color, piece->is_king, depth);

	return start;
}

std::vector<Board::TreeNodePtr> Board::jumps_by_color(Piece::Color color, uint8_t depth)
{
	Piece** pieces = nullptr;
	if (color == Piece::Color::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	std::vector<Board::TreeNodePtr> moves;
	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		TreeNodePtr treePtr = possible_jumps(pieces[i], depth);
		if (treePtr->jumps[Node::TOP_LEFT] || treePtr->jumps[Node::TOP_RIGHT] ||
			treePtr->jumps[Node::BOTTOM_LEFT] || treePtr->jumps[Node::BOTTOM_RIGHT])
			moves.push_back(treePtr);
	}

	return moves;
}

bool Board::has_possible_jumps(Piece::Color color)
{
	Piece** pieces = nullptr;
	if (color == Piece::Color::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		TreeNodePtr treePtr = possible_jumps(pieces[i], 1);
		if (treePtr->jumps[Node::TOP_LEFT] || treePtr->jumps[Node::TOP_RIGHT] ||
			treePtr->jumps[Node::BOTTOM_LEFT] || treePtr->jumps[Node::BOTTOM_RIGHT])
			return true;
	}

	return false;
}

inline Board::TreeNodePtr Board::discover_jump(TreeNodePtr root_node, Piece::Color color, uint8_t direction)
{
	if (root_node == nullptr)
		return nullptr;

	Node* tree_node = root_node->pos->adjacents[direction];
	if (tree_node != nullptr && tree_node->piece != nullptr && tree_node->piece->color != color)
	{
		// We have a piece, now check for emptiness in [direction]
		if (tree_node->adjacents[direction] != nullptr && tree_node->adjacents[direction]->piece == nullptr)
		{
			return build_tree_node(tree_node->adjacents[direction], tree_node);
		}
	}

	return nullptr;
}

void Board::discover_jumps(TreeNodePtr tree_node, Piece::Color color, bool is_king, uint8_t depth)
{
	if (depth == 0 || tree_node == nullptr || tree_node->pos == nullptr)
		return;
    
	int left, right, oleft, oright;
	if (color == Piece::Red) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
		oleft = Node::TOP_LEFT;
		oright = Node::TOP_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
		oleft = Node::BOTTOM_LEFT;
		oright = Node::BOTTOM_RIGHT;
	}

	TreeNodePtr jump = discover_jump(tree_node, color, left);
	if (jump != nullptr && jump->pos->adjacents[oright] != tree_node->killed)
	{
		tree_node->jumps[left] = jump;
		discover_jumps(jump, color, is_king, depth - 1);
	}

	jump = discover_jump(tree_node, color, right);
	if (jump != nullptr && jump->pos->adjacents[oleft] != tree_node->killed)
	{
		tree_node->jumps[right] = jump;
		discover_jumps(jump, color, is_king, depth - 1);
	}

	if (is_king)
	{
		jump = discover_jump(tree_node, color, oleft);
		if (jump != nullptr && jump->pos->adjacents[right] != tree_node->killed)
		{
			tree_node->jumps[oleft] = jump;
			discover_jumps(jump, color, is_king, depth - 1);
		}

		jump = discover_jump(tree_node, color, oright);
		if (jump != nullptr && jump->pos->adjacents[left] != tree_node->killed)
		{
			tree_node->jumps[oright] = jump;
			discover_jumps(jump, color, is_king, depth - 1);
		}
	}
}

inline std::pair<uint8_t, Board::TreeNodePtr> Board::longest_jump(Piece* piece)
{
	TreeNodePtr root = build_tree_node(piece->location);
	std::pair<uint8_t, TreeNodePtr> longest_jump = discover_longest_jump(root, piece->color, piece->is_king);
	if (longest_jump.first > 0)
	{
		root->jumps[root->longest_jump] = longest_jump.second;
		return std::pair<uint8_t, TreeNodePtr>(longest_jump.first, root);
	}
	else
		return longest_jump;
}

std::pair<uint8_t, Board::TreeNodePtr> Board::discover_longest_jump(TreeNodePtr tree_node, Piece::Color color, bool is_king)
{

	int left, right, oleft, oright;
	if (color == Piece::Red) {
		left = Node::BOTTOM_LEFT;
		right = Node::BOTTOM_RIGHT;
		oleft = Node::TOP_LEFT;
		oright = Node::TOP_RIGHT;
	} else {
		left = Node::TOP_LEFT;
		right = Node::TOP_RIGHT;
		oleft = Node::BOTTOM_LEFT;
		oright = Node::BOTTOM_RIGHT;
	}

	std::pair<uint8_t, TreeNodePtr> longest_jump, last_jump;
	TreeNodePtr jump = discover_jump(tree_node, color, left);
	if (jump != nullptr && jump->pos->adjacents[oright] != tree_node->killed)
	{
		tree_node->longest_jump = left;
		longest_jump.first = 1;
		longest_jump.second = jump;


		last_jump = discover_longest_jump(jump, color, is_king);
		if (last_jump.first > 0)
		{
			// If there were more jumps discovered
			// add to longest_jump acount and attach node to tree
			longest_jump.first += last_jump.first;
			jump->jumps[jump->longest_jump] = last_jump.second;
		}
	}
	else
	{
		longest_jump.first = 0;
		longest_jump.second = TreeNodePtr(nullptr);
	}


	jump = discover_jump(tree_node, color, right);
	if (jump != nullptr && jump->pos->adjacents[oleft] != tree_node->killed)
	{
		last_jump = discover_longest_jump(jump, color, is_king);
		if (last_jump.first+1 > longest_jump.first)
		{
			tree_node->longest_jump = right;
			longest_jump.first = 1;
			longest_jump.second = jump;

			if (last_jump.first > 0)
			{
				longest_jump.first += last_jump.first;
				jump->jumps[jump->longest_jump] = last_jump.second;
			}

		}
	}

	if (is_king)
	{
		jump = discover_jump(tree_node, color, oleft);
		if (jump != nullptr && jump->pos->adjacents[right] != tree_node->killed)
		{
			last_jump = discover_longest_jump(jump, color, is_king);
			if (last_jump.first + 1 > longest_jump.first)
			{
				tree_node->longest_jump = oleft;
				longest_jump.first = 1;
				longest_jump.second = jump;

				if (last_jump.first > 0)
				{
					longest_jump.first += last_jump.first;
					jump->jumps[jump->longest_jump] = last_jump.second;
				}
			}
		}

		jump = discover_jump(tree_node, color, oright);
		if (jump != nullptr && jump->pos->adjacents[left] != tree_node->killed)
		{
			last_jump = discover_longest_jump(jump, color, is_king);
			if (last_jump.first + 1 > longest_jump.first)
			{
				tree_node->longest_jump = oright;
				longest_jump.first = 1;
				longest_jump.second = jump;

				if (last_jump.first > 0)
				{
					longest_jump.first += last_jump.first;
					jump->jumps[jump->longest_jump] = last_jump.second;
				}
			}
		}
	}

	return longest_jump;
}


std::pair<uint8_t, Board::TreeNodePtr> Board::longest_jump_by_color(Piece::Color color)
{
	Piece ** pieces = nullptr;
	if (color == Piece::Color::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	std::pair<uint8_t, TreeNodePtr> ljump(0, TreeNodePtr(nullptr));
	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		auto last_jump(longest_jump(pieces[i]));
		if (last_jump.first > ljump.first)
			ljump = last_jump;
	}

	return ljump;
}

inline int8_t Board::get_color_points(Piece::Color color)
{
	Piece **pieces;
	if (color == Piece::Red)
		pieces = red_pieces;
	else
		pieces = black_pieces;

	int8_t count = 0;
	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] != nullptr)
		{
			count++;
			if (pieces[i]->is_king)
				count++;
		}
	}

	return count;
}

inline int8_t Board::heuristic(Piece::Color max_color, Piece::Color min_color)
{
	return get_color_points(max_color) - get_color_points(min_color);
}

int8_t Board::minimax(MoveMemento& memento, uint8_t depth, Piece::Color max_color, Piece::Color min_color, bool maximizing)
{
	if (depth == 0)
		return heuristic(max_color, min_color);

	int8_t best_value = maximizing ? INT8_MIN : INT8_MAX;

	Piece::Color op_color = maximizing ? max_color : min_color;
	bool has_jumps = has_possible_jumps(op_color);
	Piece ** pieces = op_color == Piece::Color::Red ? red_pieces : black_pieces;

	for (uint8_t i = 0; i < PIECES_COUNT; i++)
	{
		if (pieces[i] == nullptr)
			continue;

		if (has_jumps)
		{
			// Assume longest jump
			std::pair<uint8_t, TreeNodePtr> optimum_jump = longest_jump(pieces[i]);
			if (optimum_jump.first > 0)
			{
				memento.make_longest_jump(optimum_jump.second);

				if (maximizing)
					best_value = std::max(best_value, minimax(memento, depth - 1, max_color, min_color, false));
				else
					best_value = std::min(best_value, minimax(memento, depth - 1, max_color, min_color, true));

				memento.rollback(optimum_jump.first);
			}
		}
		else
		{
			// If player can't make any jumps, check for best move
			TreeNodePtr moves = possible_moves(pieces[i]);
			for (uint8_t j = 0; j < 4; j++)
			{
				if (moves->jumps[j] != nullptr)
				{
					memento.move(moves->pos, moves->jumps[j]->pos);

					if (maximizing)
						best_value = std::max(best_value, minimax(memento, depth - 1, max_color, min_color, false));
					else
						best_value = std::min(best_value, minimax(memento, depth - 1, max_color, min_color, true));

					memento.rollback(1);
				}
			}
		}
	}

	if (best_value == INT8_MAX || best_value == INT8_MIN)
		return heuristic(max_color, min_color);
	else
		return best_value;
}