
#include "rook.h"

std::vector<board::position> rook::get_possible_moves()
{
	std::vector<board::position> moves;
	add_straight_line_moves(moves);
	return moves;
}
