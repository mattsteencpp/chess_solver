
#include "king.h"

std::vector<board::position> king::get_possible_moves()
{
	std::vector<board::position> moves;
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			board::position new_position(my_position.pos_x + i, my_position.pos_y + j);
			if (is_valid_move(new_position))
			{
				if (new_position != my_position)
				{
					new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
				}
				else
				{
					new_position.value = gameboard->evaluate(my_color);
				}
				moves.push_back(new_position);
			}
		}
	}
	
	return moves;
}

