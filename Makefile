CC = gcc
CFLAGS = -m64 -lpthread -lncurses

CFILES = client.c server.c echoserver.c
OBJECTS = client.o server.o echoserver.o
DOBJECTS = dclient.o dserver.o dechoserver.o
BIN = client server echoserver
DBIN = dclient dserver dechoserver

$(OBJECTS): %.o: src/%.c
	$(CC) $(CFLAGS) -o bin/$@ -c $^

$(BIN): %: %.o
	$(CC) $(CFLAGS) bin/$^ -o bin/$@

$(DOBJECTS): d%.o: src/%.c
	$(CC) $(CFLAGS) -g -o dbg/$@ -c $^

$(DBIN): %: %.o
	$(CC) $(CFLAGS) -g dbg/$^ -o dbg/$@
