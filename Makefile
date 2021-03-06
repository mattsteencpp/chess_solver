

CC=g++
CFLAGS=-O3 -fmax-errors=5 -std=c++11 -Wno-write-strings
LFLAGS=

EXEC=solver

BASES=board piece pawn rook knight bishop king queen driver
H_FILES=$(addsuffix .h,$(BASES))
CPP_FILES=$(addsuffix .cpp,$(BASES))
O_FILES=$(addsuffix .o,$(BASES))

$(EXEC): $(O_FILES) 
	$(CC) -o $(EXEC) $(LFLAGS) $(O_FILES)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c "$<"

clean:
	rm -rf *.o $(EXEC)
