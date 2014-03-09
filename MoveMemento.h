#ifndef __checkers__MoveMemento__
#define __checkers__MoveMemento__
#include <stack>
#include <utility>
class Board;
class Point;

class MoveMemento
{
public:
    typedef std::pair<Point, Point> MoveType;
    
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
