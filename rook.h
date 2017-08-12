
#ifndef ROOK_H
#define ROOK_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class rook: public piece
{
public:
	rook(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board)
	{};
	~rook();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'R'; return 'r'; }

private:
	std::vector<board::position> get_possible_moves();
};

#endif
