CC = gcc
CFLAGS = -Wall -g

all: matrix

matrix: matrix.o
	$(CC) $(CFLAGS) -o matrix matrix.o

matrix.o: matrix.c matrix.h

clean:
	rm -f *.o matrix