CC = gcc
FLAGS = -g -Og -Wall

default: test

test: datastructures.o main.o
	$(CC) $(FLAGS) main.o datastructures.o -o test

datastructures.o: datastructures.c datastructures.h
	$(CC) $(FLAGS) datastructures.c -o datastructures.o -c

main.o: main.c
	$(CC) $(FLAGS) main.c -o main.o -c

clean:
	rm -f *.o test