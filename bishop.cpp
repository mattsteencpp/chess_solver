
#include "bishop.h"

std::vector<board::position> bishop::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	add_diagonal_moves(moves, evaluating_check);
	return moves;
}
