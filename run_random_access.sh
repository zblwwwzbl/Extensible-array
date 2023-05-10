echo "array_type,time,element_size" > "./data/${1}_results.csv"
for i in {1..5}
do
    for SIZE in $(seq 8 16 2040)
    do
        gcc -g -O3 -DSIZE=$SIZE basic_access.c -o basic
        for R in {2..4}
        do
            touch ${1}.c
            make clean_base target=${1} > /dev/null
            make "target=${1}" "SIZE=$(($SIZE + 8))" "R=${R}" > /dev/null
        done
        ./basic
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