echo "array_type,time,element_size" > "./data/${1}_results.csv"
for i in {1..1}
do
    for SIZE in $(seq 12 16 2044)
    do
        gcc -g -O3 -DSIZE=$SIZE basic_array.c -o basic
        for R in {2..5}
        do
            touch ${1}.c
            make clean_base target=${1} > /dev/null
            make "target=${1}" "SIZE=$(($SIZE + 4))" "R=${R}" > /dev/null
        done
        ./basic ${1}
        ./"${1}Mono"
        ./"${1}Sliced"
        ./"${1}SQ"
        ./"${1}HAT"
        ./"${1}MS_2"
        ./"${1}MS_3"
        ./"${1}MS_4"
        make clear_target target=${1} > /dev/null
    done
    
done