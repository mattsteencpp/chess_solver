
#include "queen.h"

std::vector<board::position> queen::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	add_diagonal_moves(moves, evaluating_check);
	add_straight_line_moves(moves, evaluating_check);
	return moves;
}
