CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -pedantic -g

.PHONY: all test clean

all: build/test_ejercicio

build/test_ejercicio: src/ejercicio.c src/ejercicio.h tests/test_ejercicio.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ src/ejercicio.c tests/test_ejercicio.c

test: build/test_ejercicio
	./build/test_ejercicio

clean:
	rm -rf build
