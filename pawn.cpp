
#include "pawn.h"

bool pawn::is_valid_position(board::position new_position)
{
	if (abs(my_position.pos_x - new_position.pos_x) == 1 && abs(my_position.pos_y - new_position.pos_y) == 1)
	{
		return is_valid_diagonal_position(new_position);
	}
	return new_position.is_valid() && 
		!gameboard->is_occupied_by_color(new_position, my_color) && 
		!gameboard->is_occupied_by_color(new_position, !my_color);
}

bool pawn::is_valid_diagonal_position(board::position new_position)
{
	return new_position.is_valid() && 
		!gameboard->is_occupied_by_color(new_position, my_color) && 
		gameboard->is_occupied_by_color(new_position, !my_color);
}

bool pawn::can_be_promoted()
{
	if (my_color == PIECE_COLOR_WHITE && my_position.pos_y == 8)
		return true;
	if (my_color == PIECE_COLOR_BLACK && my_position.pos_y == 1)
		return true;
	return false;
}

std::vector<board::position> pawn::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	// check increasing moves
	int y_change = 1;
	if (my_color == PIECE_COLOR_BLACK)
	{
		// check decreasing moves
		y_change = -1;
	}
	board::position new_position(my_position);
	moves.push_back(new_position);
	board::position straight_ahead(my_position.pos_x, my_position.pos_y + y_change);
	if (is_valid_position(straight_ahead))
	{
		piece* potential_capture = gameboard->get_piece_at_position(straight_ahead);
		if (!potential_capture)
		{
			moves.push_back(straight_ahead);
			
			// on the first move, a pawn may move 2 squares forward instead of 1, assuming there is no piece one square ahead
			if ((my_color == PIECE_COLOR_WHITE && my_position.pos_y == 2) || (my_color == PIECE_COLOR_BLACK && my_position.pos_y == 7))
			{
				board::position straight_ahead_2(my_position.pos_x, my_position.pos_y + y_change + y_change);
				if (is_valid_position(straight_ahead_2))
					moves.push_back(straight_ahead_2);
			}
		}
	}
	board::position diagonal_left(my_position.pos_x - 1, my_position.pos_y + y_change);
	if (is_valid_diagonal_position(diagonal_left))
		moves.push_back(diagonal_left);
	
	board::position diagonal_right(my_position.pos_x + 1, my_position.pos_y + y_change);
	if (is_valid_diagonal_position(diagonal_right))
		moves.push_back(diagonal_right);
	return moves;
}

