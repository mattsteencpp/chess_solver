
#include "knight.h"

std::vector<board::position> knight::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	
	board::position new_position(my_position);
	new_position.value = gameboard->evaluate(my_color);
	moves.push_back(new_position);

	for (int idx = 0; idx < 8; idx++)
	{
		board::position new_position(my_position);
		new_position.pos_x += x_moves[idx];
		new_position.pos_y += y_moves[idx];
		if (is_valid_position(new_position))
		{
			new_position.value = gameboard->evaluate(my_color);
			moves.push_back(new_position);
		}
	}
	
	return moves;
}

