
#include "rook.h"

std::vector<board::position> rook::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	add_straight_line_moves(moves, evaluating_check);
	return moves;
}
