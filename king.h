
#ifndef KING_H
#define KING_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class king: public piece
{
public:
	king(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board)
	{
		piece_type = PIECE_TYPE_KING;
	};
	~king();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'K'; return 'k'; }
	std::vector<board::position> get_possible_moves(bool evaluating_check=false);
	bool can_castle_short();
	bool can_castle_long();
};

#endif
