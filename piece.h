
#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include <vector>
#include <string>

#define PIECE_COLOR_WHITE 0
#define PIECE_COLOR_BLACK 1

class piece
{
public:
	piece(int color, board::position pos, board* new_board)
	:
		my_color(color),
		my_position(pos),
		gameboard(new_board)
	{};
	~piece();

	board::position get_best_move();
	
	virtual char pretty_print() = 0;
	
	board::position get_position() { return my_position; }
	void set_position(board::position new_position);
	int get_color() { return my_color; }
	
	bool can_be_promoted() { return false; }

protected:
	virtual std::vector<board::position> get_possible_moves() = 0;
	
	bool is_valid_move(board::position new_position);
	
	void add_diagonal_moves(std::vector<board::position>& moves);
	void add_straight_line_moves(std::vector<board::position>& moves);
	
	int my_color;
	board::position my_position;
	board* gameboard;
};

#endif
