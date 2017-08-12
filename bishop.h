
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
	{};
	~bishop();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'B'; return 'b'; }

private:
	std::vector<board::position> get_possible_moves();
};

#endif
