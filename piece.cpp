
#include "piece.h"

piece::~piece()
{

}

// TODO: sort moves based on value; will probably need a custom comparator for that...
board::position piece::get_best_move()
{
	board::position pos(std::string("A1"));
	return pos;
}

// TODO: implement add_diagonal_moves
void piece::add_diagonal_moves(std::vector<board::position>& moves)
{

}

// TODO: implement add_straight_line_moves
void piece::add_straight_line_moves(std::vector<board::position>& moves)
{

}

bool piece::is_valid_move(board::position new_position)
{
	return new_position.is_valid() && 
		!gameboard->is_occupied_by_color(new_position, my_color) && 
		!gameboard->is_in_check_after_move(my_color, my_position, new_position);
}
