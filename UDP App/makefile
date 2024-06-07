CC = gcc
CFLAGS = -Wall

all: server client

server: serveurUDP.c
	$(CC) $(CFLAGS) serveurUDP.c -o server

client: clientUDP.c
	$(CC) $(CFLAGS) clientUDP.c -o client

clean:
	rm -f server client