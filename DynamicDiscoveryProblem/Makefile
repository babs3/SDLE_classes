CC = gcc
CFLAGS = -Wextra -pedantic
LIBS = -lzmq -lpthread

all: Client Worker Proxy

Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c $(LIBS)

Worker: Worker.c
	$(CC) $(CFLAGS) -o Worker Worker.c $(LIBS)

Proxy: Proxy.c
	$(CC) $(CFLAGS) -o Proxy Proxy.c $(LIBS)

clean:
	rm -f Client Worker Proxy

.PHONY: all clean
