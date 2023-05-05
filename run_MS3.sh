echo "array_type,time,element_size" > "./data/MS3_results.csv"
for i in {1..40}
do
    for SIZE in {1232..1297}
    do
        make "target=incone" "SIZE=$SIZE" "R=3" > /dev/null
        ./"inconeMono"
        make clear_target target=incone > /dev/null
    done
done