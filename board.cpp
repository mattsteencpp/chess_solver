#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"

#include <iostream>

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
			pos_x = str_pos[0] - 97;
		else if (str_pos[0] > 64)
			pos_x = str_pos[0] - 65;
		pos_y = str_pos[1] - 48;
		if (!is_valid())
		{
			// TODO: throw exception
		}
	}
	else
	{
		// TODO: throw exception
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

piece* board::get_piece_at_position(board::position position)
{
	return my_positions[position.pos_x - 1][position.pos_y - 1];

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

// TODO: implement setup_game_in_progress!
void board::setup_game_in_progress(std::vector<piece*> pieces)
{
	
}

// TODO: implement evaluate
int board::evaluate(int color)
{
	return 0;
}

// TODO: implement evaluate_after_move
int board::evaluate_after_move(int color, board::position start_pos, board::position end_pos)
{
	return evaluate(color);
}

// TODO: implement move_piece
void board::move_piece(board::position start_pos, board::position end_pos)
{

}

// TODO: implement capture_piece
void board::capture_piece(board::position pos)
{

}

// TODO: implement promote_pawn
void board::promote_pawn(board::position pos)
{
	
}

// TODO: implement is_in_check
bool board::is_in_check(int color)
{
	// iterate over pieces of the other color given the current setup
	// if any of them has, as a possible (optimal?) move, capturing the king, then return true
	
	return false;
}

// TODO: implement is_in_check_after_move
bool board::is_in_check_after_move(int color, board::position start_pos, board::position end_pos)
{
	// iterate over pieces of the other color given the current setup
	// if any of them has, as a possible (optimal?) move, capturing the king, then return true
	
	return false;
}

// TODO: implement is_in_checkmate
bool board::is_in_checkmate(int color)
{
	// how does this need to be different from is_in_check?
	return false;
}






