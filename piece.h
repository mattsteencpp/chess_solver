
#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include <vector>
#include <string>

#define PIECE_COLOR_WHITE 0
#define PIECE_COLOR_BLACK 1

#define PIECE_TYPE_NONE 0
#define PIECE_TYPE_KING 1
#define PIECE_TYPE_QUEEN 2
#define PIECE_TYPE_BISHOP 3
#define PIECE_TYPE_ROOK 4
#define PIECE_TYPE_KNIGHT 5
#define PIECE_TYPE_PAWN 6

// use most common piece valuations, with King very large to make sure protecting it is prioritized
#define PIECE_VALUE_KING 200
#define PIECE_VALUE_QUEEN 9
#define PIECE_VALUE_ROOK 5
#define PIECE_VALUE_BISHOP 3
#define PIECE_VALUE_KNIGHT 3
#define PIECE_VALUE_PAWN 1

class piece
{
public:
	piece(int color, board::position pos, board* new_board)
	:
		my_color(color),
		my_position(pos),
		gameboard(new_board),
		piece_type(PIECE_TYPE_NONE)
	{};
	~piece();
	
	virtual char pretty_print() = 0;
	
	board::position get_position() { return my_position; }
	void set_position(board::position new_position, bool should_validate_move=true);
	int get_color() { return my_color; }
	int get_opposing_color() { return !my_color; }
	
	int get_type() { return piece_type; }

	board::position get_best_move(bool evaluating_check=false);
	virtual std::vector<board::position> get_possible_moves(bool evaluating_check=false) = 0;
protected:
	bool is_valid_move(board::position new_position);
	bool is_valid_position(board::position new_position);
	
	void add_diagonal_moves(std::vector<board::position>& moves, bool evaluating_check);
	void add_straight_line_moves(std::vector<board::position>& moves, bool evaluating_check);
	
	int my_color;
	int piece_type;
	board::position my_position;
	board* gameboard;
};

#endif

