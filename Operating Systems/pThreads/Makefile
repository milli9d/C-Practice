CC=g++
CFLAGS=-g -pthread -O3
OUTPUT=matrix

all: demo00make

demo00make: demo00.cpp 
	$(CC) $^ $(CFLAGS) -o $@
	
demo00test: demo00make 
	time ./$(^)	
