echo "array_type,time,element_size" > "./data/MS3_results.csv"
for i in {1..50}
do
    for SIZE in 1104 1120 1136 1152 1168
    do
        touch insert.c
        make clean_base target=insert > /dev/null
        make "target=insert" "SIZE=$SIZE" "R=3" > /dev/null
        ./"insertMS_3"
        make clear_target target=insert > /dev/null
    done
done