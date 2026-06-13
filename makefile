CC = gcc
CFLAGS = -I$(shell brew --prefix raylib)/include -mmacosx-version-min=26.0
LIBS = $(shell brew --prefix raylib)/lib/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit

build:
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

run: build
	./main

clean:
	rm -f main	