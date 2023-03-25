CC = gcc
FLAGS = -g -Og -Wall

default: test

test: datastructures.o general.o SQarray.o main.o
	$(CC) $(FLAGS) datastructures.o general.o SQarray.o main.o -o test

SQarray.o: SQarray.c SQarray.h general.h
	$(CC) $(FLAGS) SQarray.c -o SQarray.o -c

datastructures.o: datastructures.c datastructures.h
	$(CC) $(FLAGS) datastructures.c -o datastructures.o -c

main.o: main.c
	$(CC) $(FLAGS) main.c -o main.o -c

general.o: general.c general.h
	$(CC) $(FLAGS) general.c -o general.o -c

clean:
	rm -f *.o test