CC = gcc
FLAGS = -g -O3 -Wall

all: testMono testSliced testSQ reverseMono reverseSliced reverseSQ sortMono sortSliced sortSQ heapsortMono heapsortSQ heapsortSliced matrixmultMono matrixmultSliced matrixmultSQ inconeMono inconeSQ inconeSliced

sort_test: sortMono sortSliced sortSQ

reverse_test: reverseMono reverseSliced reverseSQ

insert_test: insertMono insertSliced insertSQ

heapsort_test: heapsortMono heapsortSQ heapsortSliced

matrixmult_test: matrixmultMono matrixmultSliced matrixmultSQ

incone_test: inconeMono inconeSQ inconeSliced

test: testMono testSliced testSQ

inconeMono: incone.o monolithic.o general.o
	$(CC) $(FLAGS) -o inconeMono incone.o monolithic.o general.o

inconeSliced: incone.o sliced.o general.o
	$(CC) $(FLAGS) -o inconeSliced incone.o sliced.o general.o

inconeSQ: incone.o SQarray.o general.o
	$(CC) $(FLAGS) -o inconeSQ incone.o SQarray.o general.o

matrixmultMono: matrixmult.o monolithic.o general.o
	$(CC) $(FLAGS) -o matrixmultMono matrixmult.o monolithic.o general.o

matrixmultSliced: matrixmult.o sliced.o general.o
	$(CC) $(FLAGS) -o matrixmultSliced matrixmult.o sliced.o general.o

matrixmultSQ: matrixmult.o SQarray.o general.o
	$(CC) $(FLAGS) -o matrixmultSQ matrixmult.o SQarray.o general.o

heapsortMono: heapsort.o monolithic.o general.o
	$(CC) $(FLAGS) -o heapsortMono heapsort.o monolithic.o general.o

heapsortSliced: heapsort.o sliced.o general.o
	$(CC) $(FLAGS) -o heapsortSliced heapsort.o sliced.o general.o

heapsortSQ: heapsort.o SQarray.o general.o
	$(CC) $(FLAGS) -o heapsortSQ heapsort.o SQarray.o general.o

insertMono: insert.o monolithic.o general.o
	$(CC) $(FLAGS) -o insertMono insert.o monolithic.o general.o

insertSliced: insert.o sliced.o general.o
	$(CC) $(FLAGS) -o insertSliced insert.o sliced.o general.o

insertSQ: insert.o SQarray.o general.o
	$(CC) $(FLAGS) -o insertSQ insert.o SQarray.o general.o

sortMono: sort.o monolithic.o general.o
	$(CC) $(FLAGS) -o sortMono sort.o monolithic.o general.o

sortSliced: sort.o sliced.o general.o
	$(CC) $(FLAGS) -o sortSliced sort.o sliced.o general.o

sortSQ: sort.o SQarray.o general.o
	$(CC) $(FLAGS) -o sortSQ sort.o SQarray.o general.o

reverseMono: reversal.o monolithic.o general.o
	$(CC) $(FLAGS) -o reverseMono reversal.o monolithic.o general.o

reverseSliced: reversal.o sliced.o general.o
	$(CC) $(FLAGS) -o reverseSliced reversal.o sliced.o general.o

reverseSQ: reversal.o SQarray.o general.o
	$(CC) $(FLAGS) -o reverseSQ reversal.o SQarray.o general.o

testMono: main.o monolithic.o general.o
	$(CC) $(FLAGS) -o testMono main.o monolithic.o general.o

testSliced: main.o sliced.o general.o
	$(CC) $(FLAGS) -o testSliced main.o sliced.o general.o

testSQ: main.o SQarray.o general.o
	$(CC) $(FLAGS) -o testSQ main.o SQarray.o general.o

incone.o: incone.c general.h interface.h
	$(CC) $(FLAGS) -c incone.c

matrixmult.o: matrixmult.c general.h interface.h
	$(CC) $(FLAGS) -c matrixmult.c

heapsort.o: heapsort.c general.h interface.h
	$(CC) $(FLAGS) -c heapsort.c

insert.o: insert.c general.h interface.h
	$(CC) $(FLAGS) -c insert.c

sort.o: sort.c general.h interface.h
	$(CC) $(FLAGS) -c sort.c

reverse.o: reversal.c general.h interface.h
	$(CC) $(FLAGS) -c reversal.c

main.o: main.c general.h interface.h
	$(CC) $(FLAGS) -c main.c

SQarray.o: SQarray.c SQarray.h general.h interface.h
	$(CC) $(FLAGS) -c SQarray.c

sliced.o: sliced.c sliced.h general.h interface.h
	$(CC) $(FLAGS) -c sliced.c

monolithic.o: monolithic.c monolithic.h general.h interface.h
	$(CC) $(FLAGS) -c monolithic.c

general.o: general.c general.h
	$(CC) $(FLAGS) -c general.c

clean:
	rm -f *.o test myprogram testMono testSliced testSQ reverseMono reverseSliced reverseSQ sortMono sortSliced sortSQ heapsortMono heapsortSQ heapsortSliced matrixmultMono matrixmultSliced matrixmultSQ inconeMono inconeSQ inconeSliced