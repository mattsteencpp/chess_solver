#include "board.h"
#include "piece.h"

#include <iostream>

// TODO: implement main!
int main(int argc, char* argv[])
{
	board chessboard;
	chessboard.setup_new_game();
	chessboard.pretty_print();
}
