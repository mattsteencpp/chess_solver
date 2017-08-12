
#include "piece.h"
#include <algorithm>

piece::~piece()
{

}

void piece::set_position(board::position new_position)
{
	if (!is_valid_move(new_position))
	{
		throw "the requested move from " + my_position.pretty_print() + " to " + new_position.pretty_print() + " is not a valid move!";
	}
	my_position = new_position;
	my_position.value = 0;
}

board::position piece::get_best_move()
{
	std::vector<board::position> moves = get_possible_moves();
	std::sort(moves.begin(), moves.end());
	return moves.front();
}

bool piece::is_valid_position(board::position new_position)
{
	if (!new_position.is_valid())
		return false;
	if (gameboard->is_occupied_by_color(new_position, my_color))
		return false;
	if (gameboard->is_in_check_after_move(my_color, my_position, new_position))
		return false;
	return true;
}

bool piece::is_valid_move(board::position new_position)
{
	std::vector<board::position> moves = get_possible_moves();
	if (std::find(moves.begin(), moves.end(), new_position) == moves.end())
		return false;
	return true;
}

void piece::add_diagonal_moves(std::vector<board::position>& moves)
{
	// add current position
	board::position new_position(my_position);
	new_position.value = gameboard->evaluate(my_color);
	moves.push_back(new_position);

	// move current position in each direction until we hit the edge of the board or another piece
	while (true)
	{
		new_position.pos_x += 1;
		new_position.pos_y += 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_x += 1;
		new_position.pos_y -= 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_x -= 1;
		new_position.pos_y -= 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_x -= 1;
		new_position.pos_y += 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
}


void piece::add_straight_line_moves(std::vector<board::position>& moves)
{
	board::position new_position(my_position);
	// don't add the current position twice if we are processing moves for the queen
	if (moves.size() == 0)
	{
		new_position.value = gameboard->evaluate(my_color);
		moves.push_back(new_position);
	}
	
	// move current position in each direction until we hit the edge of the board or another piece
	while (true)
	{
		new_position.pos_x += 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_x -= 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_y += 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
	
	new_position = my_position;
	while (true)
	{
		new_position.pos_y -= 1;
		if (!is_valid_position(new_position))
			break;
		new_position.value = gameboard->evaluate_after_move(my_color, my_position, new_position);
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
}
