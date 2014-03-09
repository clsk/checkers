// Exam.cpp : Defines the entry point for the console application.
//

// 1 punto con recursividad
#include <utility>
#include <vector>
#include <iostream>

#include "Game.h"
#include "Board.h"
#include "MoveMemento.h"

using namespace std;

int main()
{
	// 1
	Game::instance().create_board();

	// 2
	Game::instance().create_pieces();

	// 3
	vector<Node*> moves;
	Game::instance().possible_moves(Game::instance().black_pieces[11], moves);
    cout << "Possible Moves for piece at: (" << Game::instance().black_pieces[11]->location->pos.x << ", " << Game::instance().black_pieces[11]->location->pos.y << ")" << endl;;
	for (vector<Node*>::iterator Iter = moves.begin(); Iter != moves.end(); ++Iter)
		cout << "Possible Move: (" << (*Iter)->pos.x << "," << (*Iter)->pos.y << ")" << endl;

    Board& board = Game::instance().get_board();
    board.print();
    cout << endl;
    MoveMemento memento = board.get_memento();
//    memento.move(Point(1,5), Point(2,4));
    memento.move(Point(4,2), Point(6,4));
    memento.move(Point(3,1), Point(4,2));
    board.print();
    Game::instance().print_possible_jumps(board.get_node(Point(7,5))->piece);

	return 0;
}

