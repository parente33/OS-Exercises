CC = gcc
CFLAGS = -Wall -g

all: server client

server: server.o vector.o
	$(CC) $(CFLAGS) server.o vector.o -o server

client: client.o
	$(CC) $(CFLAGS) client.o -o client

server.o: server.c defs.h vector.h
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c defs.h
	$(CC) $(CFLAGS) -c client.c -o client.o

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c -o vector.o

clean:
	rm -f -r *.dSYM fifo* server client *.o
