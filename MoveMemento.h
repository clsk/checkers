#ifndef __checkers__MoveMemento__
#define __checkers__MoveMemento__
#include <stack>
#include <tuple>
class Board;
class Point;

// Class somewhat similar to a memento
// It keeps track of moves and is then able to
// rollback the changes.
// This memento can ONLY be used, if the board has only been modified by it between moves and rollbacks
class MoveMemento
{
public:
    typedef std::tuple<Piece*, Node*, Node*> MoveType;
    
    MoveMemento(Board& _board);
    
    bool move(const Point& from, const Point& to);
    // Roll back n movements
    unsigned short rollback(unsigned short n);
    // Roll back all movements
    unsigned short rollback();
    
    Board& board;
    std::stack<MoveType> moves;
};

#endif /* defined(__checkers__MoveMemento__) */
