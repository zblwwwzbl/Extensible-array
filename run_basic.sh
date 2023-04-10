for i in {1..5}
do
    for SIZE in $(seq 12 16 2044)
    do
        gcc -g -O3 -Wall -DSIZE=$SIZE basic_array.c -o basic_insert
        ./basic_insert
    done
done
