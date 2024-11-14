CC = gcc
CFLAGS = -Wall -g

all: test_heap

#gcc -o test_heap -I../include -std=c99 test_heap.c ../src/heap.c
test_heap: test_heap.c heap.c
    $(CC) $(CFLAGS) -o test_heap test_heap.c heap.c

clean:
    rm -f test_heap