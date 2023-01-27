CC=gcc
CFLAGS=-Wall -std=c99

game-of-life: game-of-life.c
	$(CC) $(CFLAGS) -o game-of-life game-of-life.c

clean:
	rm -f game-of-life
	rm -rf *.o
	rm -f *~