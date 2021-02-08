CC=g++
CFLAGS=-g -O2

all: allocateAll 

allocateAll: allocateall.cpp
	$(CC) $^ $(CFLAGS) -o $@

allocateAllTest: allocateall.cpp
	$(CC) $^ $(CFLAGS) -o $@
	./$@