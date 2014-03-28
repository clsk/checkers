#ifndef _GAME
#define _GAME

#include <vector>
#include <list>
#include <cstdint>
#include <memory>
#include <utility>

#include "Board.h"
#include "Piece.h"

#define PIECES_COUNT 12

struct TreeNode
{
    Node *pos;
    Node *killed;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
};

class Game
{
public:
    typedef std::shared_ptr<::TreeNode> TreeNodePtr;
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

	std::pair<Node*, Node*> possible_moves(Piece* piece);
    TreeNodePtr possible_jumps(Piece* piece, uint8_t depth = -1);
    void print_possible_jumps(TreeNodePtr start);
    void print_possible_jumps(Piece* piece);

//private:
    TreeNodePtr build_tree_node(Node* pos, Node* killed = nullptr);
	void discover_jumps(TreeNodePtr tree_node, uint8_t direction, uint8_t depth = -1);

	static Game *m_instance;
	Board *board;
	Piece *red_pieces[PIECES_COUNT];
	Piece *black_pieces[PIECES_COUNT];
};

#endif
