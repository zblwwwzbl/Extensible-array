make "${1}_test"
echo "array_type,time,element_size" > "./data/${1}_results.csv"
for i in {1..5}
do
    ./"${1}Mono"
    ./"${1}Sliced"
    ./"${1}SQ"
done