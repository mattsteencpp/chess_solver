
#ifndef BISHOP_H
#define BISHOP_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class bishop: public piece
{
public:
	bishop(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board)
	{
		piece_type = PIECE_TYPE_BISHOP;
	};
	~bishop();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'B'; return 'b'; }
	std::vector<board::position> get_possible_moves(bool evaluating_check=false);
};

#endif
