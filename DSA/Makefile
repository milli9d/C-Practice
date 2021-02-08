CC=gcc
CFLAGS=-g 
DEPS=LinkedList.c main.c

all: LinkedList.o test clean

LinkedList.o: $(DEPS)
	$(CC) -o $@ $(CFLAGS) $^

test:
	./LinkedList.o

clean:
	rm LinkedList.o 