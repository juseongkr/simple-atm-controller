CC=g++
CFLAGS=-Werror -Wall -O3 -std=gnu++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: clean run.out

run.out: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	@rm -f $(OBJ) *.out
