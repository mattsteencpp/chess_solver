

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

#define MOVE_STATE_NORMAL 0
#define MOVE_STATE_TEST 1
#define MOVE_STATE_REVERSE 2

class piece;
class pawn;

class board
{
public:
	class position
	{
	public:
		position()
		:
			pos_x(1),
			pos_y(1),
			value(0)
		{}
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
		// note: == and != use pos_x and pos_y to compare
		// < and > use value and are defined for sorting a list of possible moves
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
	
	void move_piece(std::string str_start_pos, std::string str_end_pos);
	void move_piece(board::position start_pos, board::position end_pos);
	void move_piece(piece* piece_to_move, board::position end_pos, int move_state=MOVE_STATE_NORMAL);
	
	bool is_occupied_by_color(board::position pos, int color);
	
	bool is_in_check(int color);
	bool is_in_check(int color, board::position king_pos);
	bool is_in_checkmate(int color);
	
	char* get_color_name(int color);
	
	bool has_king_moved(int color) { return king_moved[color]; }
	bool has_king_rook_moved(int color) { return king_rook_moved[color]; }
	bool has_queen_rook_moved(int color) { return queen_rook_moved[color]; }
	
	void pretty_print();
private:
	void remove_piece(piece* piece_to_remove, int move_state=MOVE_STATE_NORMAL);
	void restore_piece(piece* piece_to_restore);
	void promote_pawn(pawn* pawn_to_promote, int move_state=MOVE_STATE_NORMAL);
	std::vector<piece*> my_black_pieces;
	std::vector<piece*> my_white_pieces;
	
	board::position king_pos[2];
	
	// if the king or the designated rook has been moved, then the king cannot castle
	bool king_moved[2];
	bool king_rook_moved[2];
	bool queen_rook_moved[2];
	
	piece* my_positions[8][8];
	
	int depth;
};

#endif
