This is a simple implementation of a chess player/solver intended to be run from a terminal window.
It was built using g++ in Ubuntu 16.04, but I would expect it to work in most C++ build environments with few changes.

It offers the ability to play a standard chess match or to setup a custom board and start playing at any point.
All standard chess moves are permitted, including pawn promotion and castling.
In addition, it contains a rudimentary move suggestion engine, which is useful mostly for identifying very valuable
offensive moves and seeking a way out of check.

To build the solver:
	Checkout all code files and the Makefile
	Navigate to the directory containing the files.
	Run make.
	
To run the solver:
	Run the command ./solver.
	Further instructions are included within the command line interface.

