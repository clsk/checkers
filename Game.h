#ifndef _GAME
#define _GAME

#include <vector>
#include <list>

#include "Board.h"
#include "Piece.h"

#define PIECES_COUNT 12
#define DIR_UP 0
#define DIR_DOWN 1

struct TreeNode
{
    Node *pos;
    TreeNode* left;
    TreeNode* right;
    int space; // filled = 1, empty = 0;
};

class Game
{
public:
    static Game &instance()
    {
        if (m_instance == NULL)
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
	std::vector<std::list<Node*> > possible_jumps(Piece* piece);

//private:
	TreeNode* build_filled_tree_node(Node* pos);
	TreeNode* build_empty_tree_node(Node* pos);
	void discover_jumps(TreeNode *tree_node, int direction);

	static Game *m_instance;
	Board *board;
	Piece *red_pieces[PIECES_COUNT];
	Piece *black_pieces[PIECES_COUNT];
};

#endif
