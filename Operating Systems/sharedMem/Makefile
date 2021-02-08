
CC=g++
CFLAGS=-g -O3
OUTNAME=shmem
SRC=sharedMem.cpp

%.o: %.c %.h
	$(CC) $^ $(CFLAGS) -o $@ 

all: shmemmake shmemtest clean

shmemmake: $(SRC)
	$(CC) $^ $(CFLAGS) -o $(OUTNAME)

shmemtest:  
	./$(OUTNAME)
	
clean:
	rm $(OUTNAME) -v

