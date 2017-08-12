
#include "pawn.h"

bool pawn::is_valid_move(board::position new_position)
{
	if (abs(my_position.pos_x - new_position.pos_x) == 1 && abs(my_position.pos_y - new_position.pos_y) == 1)
	{
		return is_valid_diagonal_move(new_position);
	}
	return new_position.is_valid() && 
		!gameboard->is_occupied_by_color(new_position, my_color) && 
		gameboard->is_occupied_by_color(new_position, !my_color) && 
		!gameboard->is_in_check_after_move(my_color, my_position, new_position);
}

bool pawn::is_valid_diagonal_move(board::position new_position)
{
	return new_position.is_valid() && 
		!gameboard->is_occupied_by_color(new_position, my_color) && 
		gameboard->is_occupied_by_color(new_position, !my_color) && 
		!gameboard->is_in_check_after_move(my_color, my_position, new_position);
}

bool pawn::can_be_promoted()
{
	if (my_color == PIECE_COLOR_WHITE && my_position.pos_y == 8)
		return true;
	if (my_color == PIECE_COLOR_BLACK && my_position.pos_y == 1)
		return true;
	return false;
}

std::vector<board::position> pawn::get_possible_moves()
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
	new_position.value = gameboard->evaluate(my_color);
	moves.push_back(new_position);
	board::position straight_ahead(my_position.pos_x, my_position.pos_y + y_change);
	if (is_valid_move(straight_ahead))
	{
		piece* potential_capture = gameboard->get_piece_at_position(straight_ahead);
		if (!potential_capture)
		{
			straight_ahead.value = gameboard->evaluate_after_move(my_color, my_position, straight_ahead);
			moves.push_back(straight_ahead);
			
			// on the first move, a pawn may move 2 squares forward instead of 1, assuming there is no piece one square ahead
			if ((my_color == PIECE_COLOR_WHITE && my_position.pos_y == 2) || (my_color == PIECE_COLOR_BLACK && my_position.pos_y == 7))
			{
				board::position straight_ahead_2(my_position.pos_x, my_position.pos_y + y_change);
				if (is_valid_move(straight_ahead_2))
				{
					straight_ahead_2.value = gameboard->evaluate_after_move(my_color, my_position, straight_ahead_2);
					moves.push_back(straight_ahead_2);
				}
			}
		}
	}
	board::position diagonal_left(my_position.pos_x - 1, my_position.pos_y + y_change);
	if (is_valid_diagonal_move(diagonal_left))
	{
		diagonal_left.value = gameboard->evaluate_after_move(my_color, my_position, diagonal_left);
		moves.push_back(diagonal_left);
	}
	
	board::position diagonal_right(my_position.pos_x + 1, my_position.pos_y + y_change);
	if (is_valid_move(diagonal_right))
	{
		diagonal_right.value = gameboard->evaluate_after_move(my_color, my_position, diagonal_right);
		moves.push_back(diagonal_right);
	}
	return moves;
}

