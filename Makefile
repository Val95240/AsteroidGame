
.PHONY: all clean

CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
LFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(shell find src/ -name "*.cpp")


all: main

main: $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

clean:
	rm -f main
