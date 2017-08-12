
#include "queen.h"

std::vector<board::position> queen::get_possible_moves()
{
	std::vector<board::position> moves;
	add_diagonal_moves(moves);
	add_straight_line_moves(moves);
	return moves;
}
