CC = gcc
FLAGS = -g -O3 -Wall

all: ${target}_test

${target}_test: ${target}.o ${target}Mono ${target}Sliced ${target}SQ ${target}HAT ${target}MS_${R} ${target}Geo

${target}Mono: ${target}.o monolithic.o general.o
	$(CC) $(FLAGS) -o ${target}Mono ${target}.o monolithic.o general.o

${target}Sliced: ${target}.o sliced.o general.o
	$(CC) $(FLAGS) -o ${target}Sliced ${target}.o sliced.o general.o

${target}SQ: ${target}.o SQarray.o general.o
	$(CC) $(FLAGS) -o ${target}SQ ${target}.o SQarray.o general.o

${target}HAT: ${target}.o HAT.o general.o
	$(CC) $(FLAGS) -o ${target}HAT ${target}.o HAT.o general.o

${target}MS_${R}: ${target}.o multisliced.o general.o
	$(CC) $(FLAGS) -o ${target}MS_${R} ${target}.o multisliced.o general.o

${target}Geo: ${target}.o geometric.o general.o
	$(CC) $(FLAGS) -o ${target}Geo ${target}.o geometric.o general.o

${target}.o: ${target}.c general.h interface.h
	$(CC) $(FLAGS) -DSIZE=${SIZE} -DR=${R} -c ${target}.c

# insert.o: insert.c general.h interface.h
# 	$(CC) $(FLAGS) -DSIZE=${SIZE} -DR=${R} -DNUM_ELE=${NUM_ELE} -c insert.c

testMS: main.o multisliced.o general.o
	$(CC) $(FLAGS) -o testMS main.o multisliced.o general.o

testHAT: main.o HAT.o general.o
	$(CC) $(FLAGS) -o testHAT main.o HAT.o general.o

main.o: main.c general.h interface.h
	$(CC) $(FLAGS) -c main.c

multisliced.o: multisliced.c general.h interface.h
	$(CC) $(FLAGS) -c multisliced.c

SQarray.o: SQarray.c SQarray.h general.h interface.h
	$(CC) $(FLAGS) -c SQarray.c

sliced.o: sliced.c sliced.h general.h interface.h
	$(CC) $(FLAGS) -c sliced.c

monolithic.o: monolithic.c monolithic.h general.h interface.h
	$(CC) $(FLAGS) -c monolithic.c

HAT.o: HAT.c general.h interface.h
	$(CC) $(FLAGS) -c HAT.c

geometric.o: geometric.c general.h interface.h
	$(CC) $(FLAGS) -c geometric.c

general.o: general.c general.h
	$(CC) $(FLAGS) -c general.c

clean:
	rm -f *.o *.exe test myprogram testMono testSliced testSQ reverseMono reverseSliced reverseSQ sortMono sortSliced sortSQ heapsortMono heapsortSQ heapsortSliced matrixmultMono matrixmultSliced matrixmultSQ inconeMono inconeSQ inconeSliced insertMono insertSQ insertSliced temp basic basic_insert

clean_base:
	rm -f ${target}.o

clear_target:
	rm -f ${target}.o ${target}Mono ${target}Sliced ${target}SQ ${target}HAT ${target}MS_2 ${target}MS_3 ${target}MS_4 ${target}Geo