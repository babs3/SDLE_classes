CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LIBS = -lzmq lpthread

all: Server Client

Server: Server.c
	$(CC) $(CFLAGS) -o Server Server.c $(LIBS)

Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c $(LIBS)

clean:
	rm -f Server Client 

.PHONY: all clean
