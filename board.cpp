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

board::board()
{
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
	while (my_black_pieces.size() > 0)
	{
		piece* next_piece = my_black_pieces.back();
		delete next_piece;
		my_black_pieces.pop_back();
	}
	while (my_white_pieces.size() > 0)
	{
		piece* next_piece = my_white_pieces.back();
		delete next_piece;
		my_white_pieces.pop_back();
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
	return value < other.value;
}

bool board::position::operator>(const position& other)
{
	return value > other.value;
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
	std::cout << " -------- " << std::endl;
	for (int y_idx = 7; y_idx > -1; y_idx--)
	{
		std::cout << "|";
		for (int x_idx = 0; x_idx < 8; x_idx++)
		{
			if (my_positions[x_idx][y_idx])
			{
				std::cout << my_positions[x_idx][y_idx]->pretty_print();
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << "|" << std::endl;
	}
	std::cout << " -------- " << std::endl;
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
	// setup white pawns
	for (int idx = 1; idx < 9; idx++)
	{
		base_position.pos_x = idx;
		pawn* next_piece = new pawn(PIECE_COLOR_WHITE, base_position, this);
		my_white_pieces.push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	}
	
	// setup other white pieces from left to right
	base_position.pos_x = 0;
	base_position.pos_y = 1;
	
	piece* next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new rook(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new knight(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new bishop(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new queen(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new king(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	white_king_pos = base_position;
	
	base_position.pos_x++;
	next_piece = (piece *)new bishop(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new knight(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new rook(PIECE_COLOR_WHITE, base_position, this);
	my_white_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	
	// setup black pawns
	base_position.pos_x = 1;
	base_position.pos_y = 7;
	for (int idx = 1; idx < 9; idx++)
	{
		base_position.pos_x = idx;
		pawn* next_piece = new pawn(PIECE_COLOR_BLACK, base_position, this);
		my_black_pieces.push_back(next_piece);
		my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	}
	
	// setup other black pieces from left to right
	base_position.pos_x = 0;
	base_position.pos_y = 8;
	
	base_position.pos_x++;
	next_piece = (piece *)new rook(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new knight(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new bishop(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new queen(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new king(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	black_king_pos = base_position;
	
	base_position.pos_x++;
	next_piece = (piece *)new bishop(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new knight(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
	
	base_position.pos_x++;
	next_piece = (piece *)new rook(PIECE_COLOR_BLACK, base_position, this);
	my_black_pieces.push_back(next_piece);
	my_positions[base_position.pos_x - 1][base_position.pos_y - 1] = next_piece;
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
				if (color == PIECE_COLOR_WHITE)
					white_king_pos = pos;
				else
					black_king_pos = pos;
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
			if (color == PIECE_COLOR_WHITE)
				my_white_pieces.push_back(next_piece);
			else
				my_black_pieces.push_back(next_piece);
		}
	}
}

// TODO: implement evaluate priority 5
int board::evaluate(int color)
{
	return 0;
}

// TODO: implement evaluate_after_move priority 6
int board::evaluate_after_move(int color, board::position start_pos, board::position end_pos)
{
	return evaluate(color);
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

void board::move_piece(piece* piece_to_move, board::position end_pos)
{
	if (is_in_check(piece_to_move->get_color()) && is_in_check_after_move(piece_to_move->get_color(), piece_to_move->get_position(), end_pos))
		throw std::string("Invalid move. The ") + get_color_name(piece_to_move->get_color()) + " player is in check. The specified move will leave the player in check, which is not allowed.";
	if (!piece_to_move)
	{
		throw "Invalid action: asked to move a piece that doesn't exist";
	}
	// note: we update the piece before we update the board because pawns require the piece on the other end to be present for diagonal moves
	board::position current_pos = piece_to_move->get_position();
	piece_to_move->set_position(end_pos);
	if (is_occupied_by_color(end_pos, piece_to_move->get_opposing_color()))
	{
		piece* piece_to_remove = get_piece_at_position(end_pos);
		remove_piece(piece_to_remove);
	}
	my_positions[current_pos.pos_x - 1][current_pos.pos_y - 1] = 0;
	my_positions[end_pos.pos_x - 1][end_pos.pos_y - 1] = piece_to_move;
	if (piece_to_move->get_type() == PIECE_TYPE_PAWN && ((pawn*) piece_to_move)->can_be_promoted())
		promote_pawn((pawn*)piece_to_move);
	else if (piece_to_move->get_type() == PIECE_TYPE_KING)
	{
		if (piece_to_move->get_color() == PIECE_COLOR_WHITE)
			white_king_pos = piece_to_move->get_position();
		else
			black_king_pos = piece_to_move->get_position();
	}
	if (is_in_check(piece_to_move->get_opposing_color()))
	{
		if (is_in_checkmate(piece_to_move->get_opposing_color()))
			printf("%s has been checkmated!\n", get_color_name(piece_to_move->get_opposing_color()));
		else
			printf("%s is in check!\n", get_color_name(piece_to_move->get_opposing_color()));
	}
}

void board::remove_piece(piece* piece_to_remove)
{
	if (!piece_to_remove)
	{
		throw "Invalid action: asked to remove a piece that doesn't exist";
	}
	int color = piece_to_remove->get_color();
	if (color == PIECE_COLOR_WHITE)
	{
		std::vector<piece*>::iterator it = std::find(my_white_pieces.begin(), my_white_pieces.end(), piece_to_remove);
		if (it == my_white_pieces.end())
		{
			throw std::string("Invalid action: the piece to be removed (") + piece_to_remove->pretty_print() + ", " + piece_to_remove->get_position().pretty_print() + ") is white but could not be found in the list of white pieces on the board.";
		}
		my_white_pieces.erase(it);
	}
	else
	{
		std::vector<piece*>::iterator it = std::find(my_black_pieces.begin(), my_black_pieces.end(), piece_to_remove);
		if (it == my_black_pieces.end())
		{
			throw std::string("Invalid action: the piece to be removed (") + piece_to_remove->pretty_print() + ", " + piece_to_remove->get_position().pretty_print() + ") is black but could not be found in the list of black pieces on the board.";
		}
		my_black_pieces.erase(it);
	}
	my_positions[piece_to_remove->get_position().pos_x - 1][piece_to_remove->get_position().pos_y - 1] = 0;
	delete piece_to_remove;
}

// if a pawn reaches the opponent's back row, it can be promoted to any piece. we always promote to queen 
// because queen has the most power and highest point value
void board::promote_pawn(pawn* pawn_to_promote)
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
	remove_piece(pawn_to_promote);
	queen* new_queen = new queen(color, old_position, this);
	if (color == PIECE_COLOR_WHITE)
	{
		my_white_pieces.push_back(new_queen);
	}
	else
	{
		my_black_pieces.push_back(new_queen);
	}
	my_positions[old_position.pos_x - 1][old_position.pos_y - 1] = new_queen;
}

bool board::is_in_check(int color)
{
	// find the king of this color and store the position
	// iterate over pieces of the other color given the current setup
	// if any of them has, as a possible move, capturing the king, then return true
	if (color == PIECE_COLOR_WHITE)
	{
		for (int idx = 0; idx < my_black_pieces.size(); idx++)
		{
			std::vector<board::position> moves = my_black_pieces[idx]->get_possible_moves();
			if (std::find(moves.begin(), moves.end(), white_king_pos) != moves.end())
			{
				return true;
			}
		}
	}
	else
	{
		for (int idx = 0; idx < my_white_pieces.size(); idx++)
		{
			std::vector<board::position> moves = my_white_pieces[idx]->get_possible_moves();
			if (std::find(moves.begin(), moves.end(), black_king_pos) != moves.end())
			{
				return true;
			}
		}
	}
	return false;
}

// TODO: implement is_in_check_after_move priority 4
bool board::is_in_check_after_move(int color, board::position start_pos, board::position end_pos)
{
	// iterate over pieces of the other color given the current setup
	// if any of them has, as a possible (optimal?) move, capturing the king, then return true
	
	return false;
}

bool board::is_in_checkmate(int color)
{
	// find the king of this color and store the position
	board::position king_pos;
	// iterate over pieces of the current color and compare their best moves
	// if, after the very best move, that color is still in check, then that color has been checkmated
	if (color == PIECE_COLOR_WHITE)
	{
		piece* best_piece_to_move = 0;
		int best_score = -1000;
		for (int idx = 0; idx < my_white_pieces.size(); idx++)
		{
			board::position best_move = my_white_pieces[idx]->get_best_move();
			if (best_move.value > best_score)
			{
				best_score = best_move.value;
				best_piece_to_move = my_white_pieces[idx];
			}
		}
		if (is_in_check_after_move(color, best_piece_to_move->get_position(), best_piece_to_move->get_best_move()))
			return true;
	}
	else
	{
		piece* best_piece_to_move = 0;
		int best_score = -1000;
		for (int idx = 0; idx < my_white_pieces.size(); idx++)
		{
			board::position best_move = my_white_pieces[idx]->get_best_move();
			if (best_move.value > best_score)
			{
				best_score = best_move.value;
				best_piece_to_move = my_white_pieces[idx];
			}
		}
		if (is_in_check_after_move(color, best_piece_to_move->get_position(), best_piece_to_move->get_best_move()))
			return true;
	}
	return false;
}






