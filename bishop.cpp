
#include "bishop.h"

std::vector<board::position> bishop::get_possible_moves()
{
	std::vector<board::position> moves;
	add_diagonal_moves(moves);
	return moves;
}
