CC      = gcc
SRC     = nbrot.c
BIN     = nbrot
OPT     = fast
MARCH   = native
MTUNE   = $(MARCH)
GDB     = 0
STD     = c99
FLAGS   = -Wall -Wextra -pedantic -pedantic-errors
LDFLAGS = -lncurses
CFLAGS  = -O$(OPT) -march=$(MARCH) -mtune=$(MTUNE) -g$(GDB) -std=$(STD) $(FLAGS)

all: compile strip

compile:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

strip:
	objcopy --strip-all $(BIN)

clean:
	rm $(BIN)
