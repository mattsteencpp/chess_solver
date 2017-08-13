#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"

#include <iostream>
#include <algorithm>


#define MOVING_INTO_CHECK_VALUE -100
#define MAX_DEPTH 3

board::board()
:	depth(0)
{
	king_moved[0] = king_moved[1] = false;
	king_rook_moved[0] = king_rook_moved[1] = false;
	queen_rook_moved[0] = queen_rook_moved[1] = false;
	
	for (int y_idx = 7; y_idx > -1; y_idx--)
	{
		for (int x_idx = 0; x_idx < 8; x_idx++)
		{
			my_positions[x_idx][y_idx] = 0;
		}
	}
}

board::~board()
{
	while (my_pieces[PIECE_COLOR_BLACK].size() > 0)
	{
		piece* next_piece = my_pieces[PIECE_COLOR_BLACK].back();
		delete next_piece;
		my_pieces[PIECE_COLOR_BLACK].pop_back();
	}
	while (my_pieces[PIECE_COLOR_WHITE].size() > 0)
	{
		piece* next_piece = my_pieces[PIECE_COLOR_WHITE].back();
		delete next_piece;
		my_pieces[PIECE_COLOR_WHITE].pop_back();
	}
}

board::position::position(std::string str_pos)
:
	value(0)
{
	if (str_pos.length() == 2)
	{
		// convert positions using ASCII characters.
		// accept either uppercase or lowercase A-H for x position
		if (str_pos[0] > 96)
		{
			pos_x = str_pos[0] - 96;
		}
		else if (str_pos[0] > 64)
		{
			pos_x = str_pos[0] - 64;
		}
		pos_y = str_pos[1] - 48;
		if (!is_valid())
		{
			throw "created a position that is off the board: " + str_pos;
		}
	}
	else
	{
		throw "tried to create a position with an invalid string: '" + str_pos + "'. Position strings must start with a letter between A and H (or between and h) for the column followed by a number between 1 and 8 for the row";
	}
};

bool board::position::is_valid()
{
	if (pos_x > 0 && pos_x < 9 && pos_y > 0 && pos_y < 9)
		return true;
	return false;
}

bool board::position::operator==(const position& other)
{
	if (pos_x == other.pos_x && pos_y == other.pos_y)
		return true;
	return false;
}

bool board::position::operator!=(const position& other)
{
	if (pos_x != other.pos_x || pos_y != other.pos_y)
		return true;
	return false;
}


bool board::position::operator<(const position& other)
{
	return value > other.value;
}

bool board::position::operator>(const position& other)
{
	return value < other.value;
}

std::string board::position::pretty_print()
{
	std::string pretty;
	pretty += ('A' + pos_x - 1);
	pretty += ('1' + pos_y - 1);
	return pretty;
}

char* board::get_color_name(int color)
{
	if (color == PIECE_COLOR_WHITE)
		return "white";
	else
		return "black";
}

void board::pretty_print()
{
	std::cout << "  a b c d e f g h  " << std::endl;
	std::cout << "  ---------------  " << std::endl;
	for (int y_idx = 7; y_idx > -1; y_idx--)
	{
		std::cout << (y_idx + 1) << "|";
		for (int x_idx = 0; x_idx < 8; x_idx++)
		{
			if (my_positions[x_idx][y_idx])
			{
				std::cout << my_positions[x_idx][y_idx]->pretty_print() << " ";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "|" << (y_idx + 1) << std::endl;
	}
	std::cout << "  ---------------  " << std::endl;
	std::cout << "  a b c d e f g h  " << std::endl;
}

piece* board::get_piece_at_position(board::position pos)
{
	if (!pos.is_valid())
		return 0;
	return my_positions[pos.pos_x - 1][pos.pos_y - 1];

}
bool board::is_occupied_by_color(board::position pos, int color)
{
	piece* p = get_piece_at_position(pos);
	if (!p || p->get_color() != color)
		return false;
	return true;
}

void board::setup_new_game()
{
	board::position base_position(1, 2);
	for (int color = PIECE_COLOR_WHITE; color <= PIECE_COLOR_BLACK; color++)
	{
		if (color == PIECE_COLOR_BLACK)
		{
			base_position.pos_y = 7;
		}
		// setup pawns
		for (int idx = 1; idx < 9; idx++)
		{
			base_position.pos_x = idx;
			pawn* next_piece = new pawn(color, base_position, this);
			my_pieces[color].push_back(next_piece);
			my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
		}
	
		// setup other pieces from left to right
		base_position.pos_x = 0;
		base_position.pos_y = 1;
		if (color == PIECE_COLOR_BLACK)
		{
			base_position.pos_y = 8;
		}
	
		piece* next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new rook(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new knight(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new bishop(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new queen(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new king(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		king_pos[color] = base_position;
	
		base_position.pos_x++;
		next_piece = (piece *)new bishop(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new knight(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
		base_position.pos_x++;
		next_piece = (piece *)new rook(color, base_position, this);
		my_pieces[color].push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	}
}

// each string in the vector should contain a 4 letter string (case insensitive)
// the first letter must be either w or b for color
// the second letter must be k, q, b, n, r, or p for piece
// 		note that n is used for knights because k is already for king
// the 3rd and fourth letters represent the algebraic notation for the position the piece should inhabit
// 		in algebraic notation, the first character is a letter from a to h representing the column
//			the second character is a number from 1 to 8 representing the row.
//		in this notation, the standard board setup has white in rows 1 and 2 and black in rows 7 and 8
// if there is already a piece in the indicated position, an error will result
void board::setup_game_in_progress(std::vector<std::string> pieces)
{
	for (int idx = 0; idx < pieces.size(); idx++)
	{
		// parse out the piece type and starting possition
		std::string current_piece = pieces[idx];
		if (current_piece.length() != 4)
		{
			throw "found an invalid instruction: '" + current_piece + "'. The string must specify the color (B or W), the piece (K, Q, B, N, R, or P) and the position (A-H for row followed by 1-8 for column) using uppercase or lowercase letters.";
		}
		int color;
		switch(current_piece[0])
		{
			case 'W':
			case 'w':
			{
				color = PIECE_COLOR_WHITE;
				break;
			}
			case 'B':
			case 'b':
			{
				color = PIECE_COLOR_BLACK;
				break;
			}
			default:
			{
				throw "found an invalid instruction: '" + current_piece + "'. The string must start with B, W, b, or w to indicate the color of the piece to be placed.";
				break;
			}
		}
		board::position pos(current_piece.substr(2,2));
		if (get_piece_at_position(pos) != 0)
		{
			throw "found an invalid instruction: '" + current_piece + "'. There is already a piece (" + get_piece_at_position(pos)->pretty_print() + ") at the specified position.";
		}
		
		// create the piece and put it on the board
		piece* next_piece;
		switch(current_piece[1])
		{
			case 'K':
			case 'k':
			{
				next_piece = (piece *)new king(color, pos, this);
				king_pos[color] = pos;
				break;
			}
			case 'Q':
			case 'q':
			{
				next_piece = (piece *)new queen(color, pos, this);
				break;
			}
			case 'B':
			case 'b':
			{
				next_piece = (piece *)new bishop(color, pos, this);
				break;
			}
			case 'N':
			case 'n':
			{
				next_piece = (piece *)new knight(color, pos, this);
				break;
			}
			case 'R':
			case 'r':
			{
				next_piece = (piece *)new rook(color, pos, this);
				break;
			}
			case 'P':
			case 'p':
			{
				next_piece = (piece *)new pawn(color, pos, this);
				break;
			}
			default:
			{
				throw "found an invalid instruction: '" + current_piece + "'. The piece type must be specified with K, Q, B, N, R, or P (using uppercase or lowercase letters).";
				break;
			}
		}
		
		if (next_piece)
		{
			my_positions[pos.pos_x - 1][pos.pos_y - 1] = next_piece;
			my_pieces[color].push_back(next_piece);
		}
		next_piece = 0;
	}
}
	
// TODO: implement evaluate priority 1
int board::evaluate(int color)
{
	int value = 0;
	if (is_in_check(color))
	{
		// we detect checkmate if the optimal move is staying put when in check, so make sure
		// that's the optimal behavior in that situation
		value = MOVING_INTO_CHECK_VALUE;
	}
	return value;
}

int board::evaluate_after_move(int color, board::position start_pos, board::position end_pos)
{
	depth++;
	// we can't evaluate every possible sequence of moves to the endgame, so set an arbitrary limit
	if (depth >= MAX_DEPTH)
	{
		// we want to bias toward movement; we detect checkmate if the optimal move is to stay put
		if (start_pos == end_pos)
			return -2;
		return -1;
	}
	
	int value = -1;
	// store piece to move and any captured piece
	piece* piece_to_move = get_piece_at_position(start_pos);
	piece* piece_at_end_pos = get_piece_at_position(end_pos);
	bool promoted = false;
	if (piece_to_move->get_type() == PIECE_TYPE_PAWN && ((pawn*)piece_to_move)->can_be_promoted())
		promoted = true;
	if (move_is_castle(piece_to_move, end_pos))
	{
		move_piece_castle(piece_to_move, end_pos, MOVE_STATE_TEST);
		
		value = evaluate(color);
		
		// manually restore the pieces
		
		// update the board grid
		my_positions[piece_to_move->get_position().pos_x - 1][piece_to_move->get_position().pos_y - 1] = 0;
		my_positions[piece_at_end_pos->get_position().pos_x - 1][piece_at_end_pos->get_position().pos_y - 1] = 0;
		my_positions[start_pos.pos_x - 1][start_pos.pos_y - 1] = piece_to_move;
		my_positions[end_pos.pos_x - 1][end_pos.pos_y - 1] = piece_at_end_pos;
	
		// update the position of each piece
		piece_to_move->set_position(start_pos, true);
		piece_at_end_pos->set_position(end_pos, true);
	}
	else
	{
		move_piece(piece_to_move, end_pos, MOVE_STATE_TEST);
	
		// if we are moving into check, the value is a very negative constant; otherwise, call evaluate
		if ((piece_to_move->get_type() != PIECE_TYPE_KING && is_in_check(piece_to_move->get_color())) ||
			(piece_to_move->get_type() == PIECE_TYPE_KING && is_in_check(piece_to_move->get_color(), end_pos)))
		{
			// we detect checkmate if the optimal move is staying put when in check, so make sure
			// that's the optimal behavior in that situation
			value = MOVING_INTO_CHECK_VALUE - 1;
		}
		else
		{
			value = evaluate(color);
		}
	
		// restore the old board
		if (promoted)
		{
			// kill the newly created piece and put the pawn back on the board
			piece* new_piece = get_piece_at_position(end_pos);
			remove_piece(new_piece);
			piece_to_move->set_position(start_pos);
			restore_piece(piece_to_move);
		}
		else
		{
			move_piece(piece_to_move, start_pos, MOVE_STATE_RESTORE);
			if (piece_at_end_pos)
				restore_piece(piece_at_end_pos);
		}
	}
	depth--;
	return value;
}

void board::restore_piece(piece* piece_to_restore)
{
	my_pieces[piece_to_restore->get_color()].push_back(piece_to_restore);
	my_positions[piece_to_restore->get_position().pos_x - 1][piece_to_restore->get_position().pos_y - 1] = piece_to_restore;
}

void board::move_piece(std::string str_start_pos, std::string str_end_pos)
{
	board::position start_pos(str_start_pos);
	board::position end_pos(str_end_pos);
	move_piece(start_pos, end_pos);
}

void board::move_piece(board::position start_pos, board::position end_pos)
{
	piece* piece_to_move = get_piece_at_position(start_pos);
	move_piece(piece_to_move, end_pos);
}

bool board::move_is_castle(piece* piece_to_move, board::position end_pos)
{
	// account for castling, in which the king moves two spaces toward a rook and the rook moves 
	// one space past the king in the other direction.
	// we denote this move here by attempting to move the king on top of the rook.
	bool castling = false;
	if (!piece_to_move)
	{
		throw "Invalid action: asked to move a piece that doesn't exist";
	}
	if (piece_to_move->get_type() == PIECE_TYPE_KING)
	{
		piece* rook_to_castle_with = get_piece_at_position(end_pos);
		if (rook_to_castle_with && rook_to_castle_with->get_type() == PIECE_TYPE_ROOK)
		{
			if (end_pos.pos_x == 8)
			{
				if (!((king*)piece_to_move)->can_castle_short())
				{
					throw "Invalid action: not allowed to castle on the short side";
				}
				else
				{
					castling = true;
				}
			}
			else if (end_pos.pos_x == 1)
			{
				if (!((king*)piece_to_move)->can_castle_long())
				{
					throw "Invalid action: not allowed to castle on the long side";
				}
				else
				{
					castling = true;
				}
			}
		}
	}
	return castling;
}

// this method assumes that move_is_castle has just returned true with the same piece_to_move and end_pos
void board::move_piece_castle(piece* piece_to_move, board::position end_pos, int move_state)
{
	// note that castling is prohibited if the king is in check, so we don't validate that here
	king_moved[piece_to_move->get_color()] = true;
	piece* rook_to_castle_with = get_piece_at_position(end_pos);
	board::position new_rook_pos;
	// castling is denoted by attempting to move the king on top of the rook in question.
	// we need to adjust the end positions for the king and the rook before making the move
	if (rook_to_castle_with && rook_to_castle_with->get_type() == PIECE_TYPE_ROOK)
	{
		if (end_pos.pos_x == 8)
		{
			king_rook_moved[piece_to_move->get_color()] = true;
			end_pos.pos_x = 7;
				new_rook_pos.pos_x = 6;
			if (piece_to_move->get_color() == PIECE_COLOR_WHITE)
				new_rook_pos.pos_y = 1;
			else
				new_rook_pos.pos_y = 8;
		}
		else if (end_pos.pos_x == 1)
		{
			queen_rook_moved[piece_to_move->get_color()] = true;
			end_pos.pos_x = 3;
			new_rook_pos.pos_x = 4;
			if (piece_to_move->get_color() == PIECE_COLOR_WHITE)
				new_rook_pos.pos_y = 1;
			else
				new_rook_pos.pos_y = 8;
		}
	}
	
	// update the board grid
	board::position current_pos = piece_to_move->get_position();
	my_positions[current_pos.pos_x - 1][current_pos.pos_y - 1] = 0;
	my_positions[end_pos.pos_x - 1][end_pos.pos_y - 1] = piece_to_move;
	my_positions[rook_to_castle_with->get_position().pos_x - 1][rook_to_castle_with->get_position().pos_y - 1] = 0;
	my_positions[new_rook_pos.pos_x - 1][new_rook_pos.pos_y - 1] = rook_to_castle_with;
	
	// update the position of each piece and the global king_pos
	piece_to_move->set_position(end_pos, true);
	king_pos[piece_to_move->get_color()] = end_pos;
	rook_to_castle_with->set_position(new_rook_pos, true);
	
	// in the right circumstances, moving the rook could put the opponent into check
	if (move_state == MOVE_STATE_NORMAL && is_in_check(piece_to_move->get_opposing_color()))
	{
		if (is_in_checkmate(piece_to_move->get_opposing_color()))
		{
			pretty_print();
			throw std::string(get_color_name(piece_to_move->get_opposing_color())) + " has been checkmated!";
		}
		else
		{
			std::cout << get_color_name(piece_to_move->get_opposing_color()) << " is in check!" << std::endl;
		}
	}
}

void board::move_piece(piece* piece_to_move, board::position end_pos, int move_state)
{
	if (move_is_castle(piece_to_move, end_pos))
	{
		move_piece_castle(piece_to_move, end_pos, move_state);
		return;
	}
	std::cout << "Attempting move from " << piece_to_move->get_position().pretty_print() << " to " << end_pos.pretty_print() << " in state " << move_state << std::endl;
	if (!piece_to_move)
	{
		throw "Invalid action: asked to move a piece that doesn't exist";
	}
	
	piece* piece_to_remove = get_piece_at_position(end_pos);
	
	// note: we update the piece before we update the board because pawns require the piece on the other end to be present for diagonal moves
	board::position current_pos = piece_to_move->get_position();
	bool should_validate_move = (move_state != MOVE_STATE_RESTORE);
	piece_to_move->set_position(end_pos, should_validate_move);
	
	if (piece_to_remove)
		remove_piece(piece_to_remove, move_state);
	
	// update the board grid
	my_positions[current_pos.pos_x - 1][current_pos.pos_y - 1] = 0;
	my_positions[end_pos.pos_x - 1][end_pos.pos_y - 1] = piece_to_move;
	
	if (piece_to_move->get_type() == PIECE_TYPE_PAWN && ((pawn*) piece_to_move)->can_be_promoted())
	{
		promote_pawn((pawn*)piece_to_move, move_state);
	}
	
	if (move_state == MOVE_STATE_NORMAL)
	{
		// update king and rook movements so we know if castling is permitted
		if (piece_to_move->get_type() == PIECE_TYPE_KING)
		{
			king_pos[piece_to_move->get_color()] = piece_to_move->get_position();
			king_moved[piece_to_move->get_color()] = true;
		}
		else if (piece_to_move->get_type() == PIECE_TYPE_ROOK)
		{
			board::position start_pos = piece_to_move->get_position();
			if (start_pos.pos_y == 8 || start_pos.pos_y == 1)
			{
				if (start_pos.pos_x == 8)
					king_rook_moved[piece_to_move->get_color()] = true;
				else if (start_pos.pos_x == 1)
					queen_rook_moved[piece_to_move->get_color()] = true;
			}
		}
		// evaluate check for both sides
		if (is_in_check(piece_to_move->get_color()))
		{
			throw std::string("Invalid move. The specified move of piece ") + piece_to_move->pretty_print() + " to " + end_pos.pretty_print() + " will leave the player in check, which is not allowed.";
		}
		else if (is_in_check(piece_to_move->get_opposing_color()))
		{
			if (is_in_checkmate(piece_to_move->get_opposing_color()))
			{
				pretty_print();
				throw std::string(get_color_name(piece_to_move->get_opposing_color())) + " has been checkmated!";
			}
			else
			{
				std::cout << get_color_name(piece_to_move->get_opposing_color()) << " is in check!" << std::endl;
			}
		}
	}
}

void board::remove_piece(piece* piece_to_remove, int move_state)
{
	if (!piece_to_remove)
	{
		throw "Invalid action: asked to remove a piece that doesn't exist";
	}
	int color = piece_to_remove->get_color();
	std::vector<piece*>::iterator it = std::find(my_pieces[color].begin(), my_pieces[color].end(), piece_to_remove);
	if (it == my_pieces[color].end())
	{
		throw std::string("Invalid action: the piece to be removed (") + piece_to_remove->pretty_print() + ", " + piece_to_remove->get_position().pretty_print() + ") could not be found in the list of pieces on the board.";
	}
	my_pieces[color].erase(it);
	my_positions[piece_to_remove->get_position().pos_x - 1][piece_to_remove->get_position().pos_y - 1] = 0;
	if (move_state != MOVE_STATE_TEST)
		delete piece_to_remove;
}

// if a pawn reaches the opponent's back row, it can be promoted to any piece. we always promote to queen 
// because queen has the most power and highest point value
void board::promote_pawn(pawn* pawn_to_promote, int move_state)
{
	if (!pawn_to_promote)
	{
		throw "Invalid action: the pawn to be promoted does not exist.";
	}
	if (!pawn_to_promote->can_be_promoted())
	{
		throw "Invalid action: the pawn cannot be promoted because it is not in the correct position.";
	}
	board::position old_position = pawn_to_promote->get_position();
	int color = pawn_to_promote->get_color();
	remove_piece(pawn_to_promote, move_state);
	queen* new_queen = new queen(color, old_position, this);
	my_pieces[color].push_back(new_queen);
	my_positions[old_position.pos_x - 1][old_position.pos_y - 1] = new_queen;
}

bool board::is_in_check(int color)
{
	return is_in_check(color, king_pos[color]);
}

bool board::is_in_check(int color, board::position king_pos)
{
	// find the king of this color and store the position
	// iterate over pieces of the other color given the current setup
	// if any of them has, as a possible move, capturing the king, then return true
	for (int idx = 0; idx < my_pieces[!color].size(); idx++)
	{
		std::vector<board::position> moves = my_pieces[!color][idx]->get_possible_moves(true);
		for (int idx = 0; idx < moves.size(); idx++)
		{
			if (moves[idx] == king_pos)
			{
				return true;
			}
		}
	}
	return false;
}

// iterate over pieces of the current color and compare their best moves
// if, after the very best move, that color is still in check, then that color has been checkmated
// note: this method assumes that color is already in check when called
bool board::is_in_checkmate(int color)
{
	piece* best_piece_to_move = 0;
	int best_score = -1000;
	board::position best_move;
	for (int idx = 0; idx < my_pieces[color].size(); idx++)
	{
		board::position next_move = my_pieces[color][idx]->get_best_move(true);
		if (next_move.value > best_score)
		{
			best_move = next_move;
			best_score = next_move.value;
			best_piece_to_move = my_pieces[color][idx];
		}
	}
	// note: if the best opponent's move is to stay put, then they can't get out of check
	if (best_piece_to_move->get_position() == best_move)
		return true;
	return false;
}






