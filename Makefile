CC = gcc
CFLAGS = -m64 -lpthread -lncurses

CFILES = client.c server.c tui.c
OBJECTS = client.o server.o tui.o
DOBJECTS = dclient.o dserver.o dtui.o
BIN = client server tui
DBIN = dclient dserver dtui

$(OBJECTS): %.o: src/%.c
	$(CC) $(CFLAGS) -o bin/$@ -c $^

$(BIN): %: %.o
	$(CC) $(CFLAGS) bin/$^ -o bin/$@

$(DOBJECTS): d%.o: src/%.c
	$(CC) $(CFLAGS) -g -o dbg/$@ -c $^

$(DBIN): %: %.o
	$(CC) $(CFLAGS) -g dbg/$^ -o dbg/$@

delete:
	@echo "removing all not source files"
	@rm bin/main bin/main.o
	@rm debug/main-debug debug/main-debug.o
