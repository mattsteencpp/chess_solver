
#ifndef KNIGHT_H
#define KNIGHT_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class knight: public piece
{
public:
	knight(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board),
		x_moves{1, 1, -1, -1, 2, 2, -2, -2},
		y_moves{2, -2, 2, -2, 1, -1, 1, -1}
	{
		piece_type = PIECE_TYPE_KNIGHT;
		piece_value = PIECE_VALUE_KNIGHT;
	};
	~knight();

	// King also starts with K, so use N for night, as is tradition
	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'N'; return 'n'; }

	std::vector<board::position> get_possible_moves(bool evaluating_check=false);
private:
	// knight moves are irregular, so define arrays listing the 8 possible moves from any position
	const int x_moves[8];
	const int y_moves[8];
};

#endif
