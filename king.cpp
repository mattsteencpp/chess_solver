
#include "king.h"

std::vector<board::position> king::get_possible_moves(bool evaluating_check)
{
	std::vector<board::position> moves;
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			board::position new_position(my_position.pos_x + i, my_position.pos_y + j);
			if (is_valid_position(new_position))
				moves.push_back(new_position);
		}
	}
	// check on castling (to either side)
	// when performing this move, will be listed as starting with the king; move_piece will have to be updated to handle that (and almost certainly to verify that castling is allowed in that scenario...)
	
	if (!evaluating_check && can_castle_short())
	{
		board::position new_position(8, my_position.pos_y);
		moves.push_back(new_position);
	}
	if (!evaluating_check && can_castle_long())
	{
		board::position new_position(1, my_position.pos_y);
		moves.push_back(new_position);
	}
	
	return moves;
}

// rules of castling:
// in castling, two pieces are moved as part of a single turn
// the king moves two spaces along the back row toward a rook
// the rook moves one space past the king in the other direction
// the king may castle on either the short side (king's side)
// or the long side (queen's side)
//
// castling is not permitted in the following cases:
// the king has been moved at any point in the game
// the rook being castled with has been moved at any point in the game
// there are pieces standing between the king and the rook
// the king is in check
// the king would move into check
// the king would pass through a square that is in check

// note that we don't look at moving into check here because that 
// scenario will be covered by evaluate_after_move if we get that far
bool king::can_castle_short()
{
	if (gameboard->has_king_moved(my_color))
		return false;
	if (gameboard->has_king_rook_moved(my_color))
		return false;
	// there are pieces standing between the king and the rook
	board::position king_pos = my_position;
	king_pos.pos_x++;
	if (gameboard->get_piece_at_position(king_pos) != 0)
		return false;
	king_pos.pos_x++;
	if (gameboard->get_piece_at_position(king_pos) != 0)
		return false;
	// the king is currently in check
	if (gameboard->is_in_check(my_color))
		return false;
	// move back to the middle square to see if the king would
	// move through check. we do this afterward because it's
	// a more time-consuming process
	king_pos.pos_x--;
	// the king would pass through a square that is in check
	if (gameboard->is_in_check(my_color, king_pos))
		return false;
	return true;
}

bool king::can_castle_long()
{
	if (gameboard->has_king_moved(my_color))
		return false;
	if (gameboard->has_queen_rook_moved(my_color))
		return false;
	// there are pieces standing between the king and the rook
	board::position king_pos = my_position;
	king_pos.pos_x--;
	if (gameboard->get_piece_at_position(king_pos) != 0)
		return false;
	king_pos.pos_x--;
	if (gameboard->get_piece_at_position(king_pos) != 0)
		return false;
	king_pos.pos_x--;
	if (gameboard->get_piece_at_position(king_pos) != 0)
		return false;
	// the king is currently in check
	if (gameboard->is_in_check(my_color))
		return false;
	// move back to the middle square to see if the king would
	// move through check. we do this afterward because it's
	// a more time-consuming process
	king_pos.pos_x += 2;
	// the king would pass through a square that is in check
	if (gameboard->is_in_check(my_color, king_pos))
		return false;
	return true;
}
