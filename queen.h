
#ifndef QUEEN_H
#define QUEEN_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class queen: public piece
{
public:
	queen(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board)
	{
		piece_type = PIECE_TYPE_QUEEN;
	};
	~queen();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'Q'; return 'q'; }
	std::vector<board::position> get_possible_moves();
};

#endif
