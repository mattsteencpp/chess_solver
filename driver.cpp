#include "board.h"
#include "piece.h"

#include <iostream>

void show_help(bool in_setup, board chessboard);
void show_grid_help(board chessboard);
int do_custom_setup(board& chessboard);

int main(int argc, char* argv[])
{
	board chessboard;

	try
	{
		std::cout << "Welcome to Chess Solver version 0.1!"  << std::endl;
		std::cout << "Written by Matt Steen"  << std::endl << std::endl;
		std::cout << "If you are interested in learning the rules of chess or more about the game,"  << std::endl;
		std::cout << "there are numerous books and online resources. We recommend https://www.chess.com and "  << std::endl;
		std::cout << "https://en.wikipedia.org/wiki/Chess" << std::endl << std::endl;
	
		bool in_setup = true;
		show_help(in_setup, chessboard);
		
		std::string command;
		
		while (true)
		{
			std::cout << ">>>";
			std::cin >> command;
		
			if (command == "n" || command == "N")
			{
				chessboard.setup_new_game();
				break;
			}
			else if (command == "c" || command == "C")
			{
				if (do_custom_setup(chessboard) == 1);
					return 0;
				break;
			}
			else if (command == "h" || command == "H")
			{
				show_help(in_setup, chessboard);
			}
			else if (command == "q" || command == "q")
			{
				return 0;
			}
			else
			{
				std::cout << "Invalid input. Please try again."  << std::endl;
				show_help(in_setup, chessboard);
			}
		}	
	
		int color = PIECE_COLOR_WHITE;
		std::string start_pos_str, end_pos_str;
		in_setup = false;
		show_help(in_setup, chessboard);
		while (true)
		{
			std::cout << ">>>";
			std::cin >> command;
		
			if (command == "m" || command == "M")
			{
				std::cin >> start_pos_str;
				std::cin >> end_pos_str;
				
				board::position start_pos(start_pos_str);
				if (!start_pos.is_valid())
				{
					std::cout << "The starting position you entered is not valid. Please try again." << std::endl;
					continue;
				}
				
				board::position end_pos(end_pos_str);
				if (!end_pos.is_valid())
				{
					std::cout << "The ending position you entered is not valid. Please try again." << std::endl;
					continue;
				}
				
				piece* piece_to_move = chessboard.get_piece_at_position(start_pos);
				if (piece_to_move && piece_to_move->get_color() != color)
				{
					std::cout << "The piece you requested to move is " << chessboard.get_color_name(color);
					std::cout << ", but it is " << chessboard.get_color_name(!color) << "'s turn. Please try again." << std::endl;
					continue;
				}
				
				try
				{
					chessboard.move_piece(start_pos, end_pos);
					chessboard.pretty_print();
					color = !color;
				}
				catch(std::string message)
				{
					if (message.find("checkmate") != std::string::npos)
					{
						std::cout << message << std::endl;
						std::cout << "The game is over!" << std::endl;
						return 0;
					}
					else
					{
						std::cout << "An error occurred while trying to make the requested move. The error message was '" << message << "'" << std::endl;
					}
				}
				catch(const char* message)
				{
					std::cout << "An error occurred while trying to make the requested move. The error message was '" << message << "'" << std::endl;
				}
			}
			else if (command == "s" || command == "S")
			{
				chessboard.suggest_move(color);
			}
			else if (command == "l" || command == "L")
			{
				std::cin >> start_pos_str;
				board::position start_pos(start_pos_str);
				if (!start_pos.is_valid())
				{
					std::cout << "The starting position you entered is not valid. Please try again." << std::endl;
					continue;
				}
				
				piece* piece_to_suggest = chessboard.get_piece_at_position(start_pos);
				if (!piece_to_suggest)
				{
					std::cout << "We could not find a piece at the requested position. Please try again." << std::endl;
					continue;
				}
				
				if (piece_to_suggest->get_color() != color)
				{
					std::cout << "The piece you requested suggestions for is " << chessboard.get_color_name(color);
					std::cout << ", but it is " << chessboard.get_color_name(!color) << "'s turn. Please try again." << std::endl;
					continue;
				}

				std::cout << "The possible moves for piece " << piece_to_suggest->pretty_print() << " are: " << std::endl;
				board::position best_move = piece_to_suggest->get_best_move(false);
				
				std::vector<board::position> moves = piece_to_suggest->get_possible_moves(false);
				for (int idx = 0; idx < moves.size(); idx++)
				{
					std::cout << moves[idx].pretty_print();
					if (moves[idx] == best_move)
						std::cout << " (recommended)";
					std::cout << std::endl;
				}
				
			}
			else if (command == "h" || command == "H")
			{
				show_help(in_setup, chessboard);
			}
			else if (command == "q" || command == "Q")
			{
				return 0;
			}
			else
			{
				std::cout << "Invalid input. Please try again."  << std::endl;
				show_help(in_setup, chessboard);
			}
		}
	}
	catch(std::string message)
	{
		if (message.find("checkmate") != std::string::npos)
			std::cout << message << std::endl;
		else
			std::cout << "An exception occurred while trying to play out the game: " << message << std::endl;
	}
	catch(const char* message)
	{
		std::cout << "An exception occurred while trying to play out the game: " << message << std::endl;
	}
}


void show_help(bool in_setup, board chessboard)
{
	if (in_setup)
	{
		std::cout << "To start a new standard game, press n." << std::endl;
		std::cout << "To setup a custom game board, press c." << std::endl;
		std::cout << "To quit the game, press q." << std::endl;
		std::cout << "To see the help again, press h." << std::endl;
	}
	else
	{
		show_grid_help(chessboard);
		std::cout << "Note that white pieces are noted with capital letters, and black pieces are noted with" << std::endl;
		std::cout << "lowercase letters. According to tradition, white always goes first." << std::endl << std::endl;
		
		std::cout << "To move a piece, press m followed by two valid locations." << std::endl;
		std::cout << "    Note: to castle a king (when permitted), request to move the king on top of the rook." << std::endl;
		std::cout << "To ask for a suggestion, press s." << std::endl;
		std::cout << "To list possible moves and get a suggestion for a particular piece, press l followed by the location of the piece." << std::endl;
		std::cout << "To quit the game, press q." << std::endl;
	
	}
	std::cout << std::endl;
}

void show_grid_help(board chessboard)
{
	chessboard.pretty_print();
	std::cout << std::endl;
	std::cout << "The numbers and letters around the grid are used to specify locations on the board." << std::endl;
	std::cout << "Letters always come first, and they may be uppercase or lowercase." << std::endl;
	std::cout << "In a standard chess setup, white pieces are aligned along the bottom (rows 1 and 2), and black " << std::endl;
	std::cout << "pieces are aligned along the top (rows 7 and 8)" << std::endl << std::endl;
}

int do_custom_setup(board& chessboard)
{
	std::cout << "Welcome to custom setup. Here is the board we will be using:" << std::endl << std::endl;
	show_grid_help(chessboard);
	std::cout << "To add your own pieces, enter a series of strings with 4 characters, each on its own line." << std::endl;
	std::cout << "Each string should start with either W or B for white or black." << std::endl;
	std::cout << "The next character should be one of the following:" << std::endl;
	std::cout << "K for king" << std::endl;
	std::cout << "Q for queen" << std::endl;
	std::cout << "B for bishop" << std::endl;
	std::cout << "N for knight (because K is already taken)" << std::endl;
	std::cout << "R for rook (also known as a castle)" << std::endl;
	std::cout << "P for pawn" << std::endl << std::endl;
	std::cout << "The final two characters give the location of the piece on the grid (letter first)." << std::endl;
	std::cout << "For example, to add a white rook in the bottom left corner, you would enter the string 'WRA1'" << std::endl << std::endl;
	std::cout << "Enter the pieces you would like to see on the board in any order." << std::endl;
	std::cout << "When you are finished, press D to start the game" << std::endl;
	
	std::string command;
	while (true)
	{
		std::cout << ">>>";
		std::cin >> command;
		
		if (command == "D" || command == "d")
			break;
		
		if (command == "q")
			return 1;
		
		try
		{
			chessboard.add_piece(command);
			chessboard.pretty_print();
		}
		catch(std::string message)
		{
			std::cout << "We couldn't add the piece you requested. The error message was '" << message << "'" << std::endl;
		}
		catch(const char* message)
		{
			std::cout << "We couldn't add the piece you requested. The error message was '" << message << "'" << std::endl;
		}
	}
	return 0;
}

