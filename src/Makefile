CC = gcc
CFLAGS = -std=c99 -Wall -g
OBJ = main.o liste.o arbrebinaire.o btrees.o maxheap.o minheap.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
