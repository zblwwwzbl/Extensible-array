echo "array_type,time,element_size" > "./data/insert_length_results.csv"
for i in {1..20}
do
    for NUM_ELE in {1024,32768,1048576,33554432}
    do
        gcc -g -O3 -DSIZE=8 -DNUM_ELE=$NUM_ELE basic_array.c -o basic
        for R in {2..5}
        do
            touch ${1}.c
            make clean_base target=${1} > /dev/null
            make "target=${1}" "SIZE=16" "R=${R}" "NUM_ELE=$NUM_ELE" > /dev/null
        done
        ./basic ${1}
        ./"${1}Mono"
        ./"${1}Sliced"
        ./"${1}SQ"
        ./"${1}HAT"
        ./"${1}MS_2"
        ./"${1}MS_3"
        ./"${1}MS_4"
        ./"${1}Geo"
        make clear_target target=${1} > /dev/null
    done
    
done