CC = gcc
CFLAGS = -Wall -Wextra

all: test_frag.out

test_frag.out: tests/test_frag.c src/allocator.c
	$(CC) $(CFLAGS) tests/test_frag.c -o test_frag.out

run: test_frag.out
	./test_frag.out

clean:
	rm -f test_frag.out

.PHONY: all run clean
