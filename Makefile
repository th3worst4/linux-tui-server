CC = gcc
CFLAGS = -m64

CFILES = client.c server.c tui.c
OBJECTS = client.o server.o tui.o
DOBJECTS = dclient.o dserver.o dtui.o
BIN = client server tui
DBIN = dclient dserver dtui

all: final debug

final: $(OBJECTS)
	$(CC) $(CFLAGS) $(addprefix bin/, $(OBJECTS)) -o bin/main
	@echo "final application built successfully"
	@echo "you can find it at 'bin/main'"
	@echo " "

$(OBJECTS): %.o: src/%.c
	$(CC) $(CFLAGS) -o bin/$@ -c $^

$(BIN): %: %.o
	$(CC) $(CFLAGS) bin/$^ -o bin/$@

debug: $(DOBJECTS)
	$(CC) $(CFLAGS) -g $(addprefix debug/, $(DOBJECTS)) -o debug/main-debug
	@echo "debug application built successfully"
	@echo "you can run gdb on 'debug/main-debug'"
	@echo " "

$(DOBJECTS): %-debug.o: src/%.c
	$(CC) $(CFLAGS) -g -o debug/$@ -c $^


delete:
	@echo "removing all not source files"
	@rm bin/main bin/main.o
	@rm debug/main-debug debug/main-debug.o
