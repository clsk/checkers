#ifndef __checkers__MoveMemento__
#define __checkers__MoveMemento__
#include <stack>
#include <tuple>
class Board;
struct Point;

struct MMove
{
	MMove(Piece* _piece, Node* _from, Node* _to, bool _crowned, Piece* _killed = nullptr, Node* _killed_pos = nullptr) : 
	piece(_piece), from(_from), to(_to), crowned(_crowned), killed(_killed), killed_pos(_killed_pos)
	{
	}
	Piece* piece;
	Node* from;
	Node* to;
	bool crowned;
	Piece* killed;
	Node* killed_pos;
};

// Class somewhat similar to a memento
// It keeps track of moves and is then able to
// rollback the changes.
// This memento can ONLY be used, if the board has only been modified by it between moves and rollbacks
class MoveMemento
{
public:
    MoveMemento(Board& _board, bool _scoped = false);
	~MoveMemento();
    
    bool move(const ::Point& from, const ::Point& to);
	bool move(Node* from, Node* to);
	bool jump(Node* from, Node* to, Piece* killed);
	bool make_longest_jump(Board::TreeNodePtr);
	void remove_piece(Piece* piece);
	void unremove_piece(Piece* piece, Node* location);


    // Roll back n movements
    unsigned short rollback(unsigned short n);
    // Roll back all movements
    unsigned short rollback();
    
    Board& board;
    std::stack<MMove> moves;
	bool scoped;
};

#endif /* defined(__checkers__MoveMemento__) */
