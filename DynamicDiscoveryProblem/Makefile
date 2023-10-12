CC = gcc
CFLAGS = -Wextra -pedantic
LIBS = -lzmq -lpthread

all: Client Worker Broker

Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c $(LIBS)

Worker: Worker.c
	$(CC) $(CFLAGS) -o Worker Worker.c $(LIBS)

Broker: Broker.c
	$(CC) $(CFLAGS) -o Broker Broker.c $(LIBS)

clean:
	rm -f Client Worker Broker

.PHONY: all clean
