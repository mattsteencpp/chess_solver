
#ifndef PAWN_H
#define PAWN_H

#include "board.h"
#include "piece.h"
#include <vector>
#include <string>

class pawn: public piece
{
public:
	pawn(int color, board::position pos, board* new_board)
	:
		piece(color, pos, new_board)
	{};
	~pawn();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'P'; return 'p'; }

private:
	std::vector<board::position> get_possible_moves();
	
	bool is_valid_diagonal_move(board::position new_position);
};

#endif
