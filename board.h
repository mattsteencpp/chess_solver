

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class piece;
class pawn;

class board
{
public:
	class position
	{
	public:
		position(std::string str_pos);
		position(const position& source)
		:
			pos_x(source.pos_x),
			pos_y(source.pos_y),
			value(source.value)
		{}
		position(int x, int y)
		:	pos_x(x),
			pos_y(y),
			value(0)
		{};
		bool operator==(const position& other);
		bool operator!=(const position& other);
		bool operator<(const position& other);
		bool operator>(const position& other);
		int pos_x;
		int pos_y;
		int value;
		bool is_valid();
		std::string pretty_print();
	};

	board();
	~board();
	
	void setup_new_game();
	void setup_game_in_progress(std::vector<std::string> pieces);
	
	piece* get_piece_at_position(board::position pos);
	
	int evaluate(int color);
	
	int evaluate_after_move(int color, board::position start_pos, board::position end_pos);
	
	// TODO: add support for castling priority 7
	
	// TODO: determine what system will be used to evaluate potential moves (as opposed to the current state of the board)
	// we will need to be able to undo changes that are made!
	
	void move_piece(std::string str_start_pos, std::string str_end_pos);
	void move_piece(board::position start_pos, board::position end_pos);
	void move_piece(piece* piece_to_move, board::position end_pos);
	
	bool is_occupied_by_color(board::position pos, int color);
	
	bool is_in_check(int color);
	bool is_in_check_after_move(int color, board::position start_pos, board::position end_pos);
	bool is_in_checkmate(int color);
	
	void pretty_print();
private:
	void remove_piece(piece* piece_to_remove);
	void promote_pawn(pawn* pawn_to_promote);
	std::vector<piece*> my_black_pieces;
	std::vector<piece*> my_white_pieces;
	
	piece* my_positions[8][8];
};

#endif
