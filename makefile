CC=gcc
CFLAGS=-I.

make: main.o mazeGenerator.o mazeSolver.o
	$(CC) $(CFLAGS) -o main main.o mazeGenerator.o mazeSolver.o

mazeGenerator.o: mazeGenerator.c
	$(CC) $(CFLAGS) -c mazeGenerator.c

mazeSolver.o: mazeSolver.c
	$(CC) $(CFLAGS) -c mazeSolver.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

clean:
	rm -f *.o main
