#ifndef _GAME
#define _GAME

#include <vector>
#include <list>
#include <cstdint>
#include <memory>

#include "Board.h"
#include "Piece.h"

#define PIECES_COUNT 12

struct TreeNode
{
    Node *pos;
    Node *kill;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    int space; // filled = 1, empty = 0;
};

class Game
{
public:
    typedef std::shared_ptr<TreeNode> TreeNodePtr;
    static Game &instance()
    {
        if (m_instance == nullptr)
            m_instance = new Game();

        return *m_instance;
    }

	void create_board()
	{
		board = new Board();
	}

	Board& get_board() { return *board; }
	void create_pieces();

	void possible_moves(Piece* piece, std::vector<Node*> &nodes);
	void possible_moves_by_color(Piece::Color color, std::vector<Node*> &nodes);
    TreeNodePtr possible_jumps(Piece* piece);
    void print_possible_jumps(TreeNodePtr start);
    void print_possible_jumps(Piece* piece);

//private:
    TreeNodePtr build_filled_tree_node(Node* pos);
    TreeNodePtr build_empty_tree_node(Node* pos);
	void discover_jumps(TreeNodePtr tree_node, uint8_t direction);

	static Game *m_instance;
	Board *board;
	Piece *red_pieces[PIECES_COUNT];
	Piece *black_pieces[PIECES_COUNT];
};

#endif
