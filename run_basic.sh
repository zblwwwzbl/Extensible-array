for i in {1..5}
do
    for SIZE in $(seq 12 16 2044)
    do
        gcc -g -DSIZE=$SIZE basic_array.c -o basic_insert
        ./basic_insert
    done
done
