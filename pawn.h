
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
	{
		piece_type = PIECE_TYPE_PAWN;
	};
	~pawn();
	
	bool can_be_promoted();

	char pretty_print() { if (my_color == PIECE_COLOR_WHITE) return 'P'; return 'p'; }
	
	std::vector<board::position> get_possible_moves(bool evaluating_check=false);
private:
	bool is_valid_position(board::position new_position);
	
	bool is_valid_diagonal_position(board::position new_position);
};

#endif
