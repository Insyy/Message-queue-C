CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g -D_GNU_SOURCE

all: Common Washer Client Server

Common: msq-common.c msq-common.h
	$(CC) -c -o msq-common.o msq-common.c $(CFLAGS)

Washer: msq-washer.c msq-washer.h
	$(CC) -c -o msq-washer.o msq-washer.c $(CFLAGS)

Client: msq-client.c msq-common.o msq-washer.o
	$(CC)  -o msq-client.out msq-client.c msq-common.o msq-washer.o $(CFLAGS)

Server: msq-server.c msq-common.o msq-washer.o
	$(CC)  -o msq-server.out msq-server.c msq-common.o msq-washer.o $(CFLAGS)

clean:
	rm *.o

s: Server
	./msq-server.out

c: Client
	./msq-client.out