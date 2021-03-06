#include "piece.h"
#include <algorithm>
#include <iostream>
#include <random>

piece::~piece()
{

}

void piece::set_position(board::position new_position, bool should_validate_move)
{
	if (!should_validate_move)
	{
		if (!new_position.is_valid())
		{
			throw "the requested move from " + my_position.pretty_print() + " is a move off the board!";
		}
	}
	else if (!is_valid_move(new_position))
	{
		throw "the requested move from " + my_position.pretty_print() + " to " + new_position.pretty_print() + " is not a valid move!";
	}
	my_position = new_position;
	my_position.value = 0;
}

board::position piece::get_best_move(bool evaluating_check)
{
	std::vector<board::position> moves = get_possible_moves(evaluating_check);
	for (int idx = 0; idx < moves.size(); idx++)
	{
		board::position next_move = moves[idx];
		if (next_move != my_position)
			moves[idx].value = gameboard->evaluate_after_move(my_color, my_position, next_move);
		else
			moves[idx].value = gameboard->evaluate(my_color);
	}
	std::sort(moves.begin(), moves.end());
	// if we have a tie, randomly choose among the options
	int score = moves.front().value;
	int stay_put_idx = -1;
	int tied_moves = 0;
	int best_move_idx = 0;
	for (int idx = 0; idx < moves.size(); idx++)
	{
		if (moves[idx].value == score)
		{
			tied_moves++;
			if (score > MOVING_INTO_CHECK_VALUE && stay_put_idx == -1 && moves[idx] == my_position)
				stay_put_idx = idx;
		}
		else
			break;
	}
	if (tied_moves > 1)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribution(0, tied_moves - 1);
		best_move_idx = distribution(gen);
		// try to avoid staying put if at all possible
		while (best_move_idx == stay_put_idx)
		{
			best_move_idx = distribution(gen);
		}
	}
	return moves[best_move_idx];
}

bool piece::is_valid_position(board::position new_position)
{
	if (!new_position.is_valid())
		return false;
	if (gameboard->is_occupied_by_color(new_position, my_color))
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

void piece::add_diagonal_moves(std::vector<board::position>& moves, bool evaluating_check)
{
	// add current position
	board::position new_position(my_position);
	moves.push_back(new_position);

	// move current position in each direction until we hit the edge of the board or another piece
	// note that is_valid_position checks for collisions with my_color
	while (true)
	{
		new_position.pos_x += 1;
		new_position.pos_y += 1;
		if (!is_valid_position(new_position))
			break;
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
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
}

void piece::add_straight_line_moves(std::vector<board::position>& moves, bool evaluating_check)
{
	board::position new_position(my_position);
	// don't add the current position twice if we are processing moves for the queen
	if (moves.size() == 0)
		moves.push_back(new_position);
	
	// move current position in each direction until we hit the edge of the board or another piece
	// note that is_valid_position checks for collisions with my_color
	while (true)
	{
		new_position.pos_x += 1;
		if (!is_valid_position(new_position))
			break;
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
		moves.push_back(new_position);
		if (gameboard->is_occupied_by_color(new_position, !my_color))
			break;
	}
}
