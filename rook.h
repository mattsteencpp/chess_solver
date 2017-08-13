
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
	{
		piece_type = PIECE_TYPE_ROOK;
		piece_value = PIECE_VALUE_ROOK;
	};
	~rook();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'R'; return 'r'; }
	std::vector<board::position> get_possible_moves(bool evaluating_check=false);
};

#endif
