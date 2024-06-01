CC = g++
CFLAGS = -O2 -Wall -lm
SRC=$(wildcard ../*.c)
OBJ=$(wildcard *.o)

build_binary: build_objects
	$(CC) $(CFLAGS) $(OBJ) -o newton_interp.out

build_objects:
	$(CC) -c $(CFLAGS) $(SRC)

clean:
	rm -f ./*.o
