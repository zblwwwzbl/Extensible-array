make "heapsort_test"
echo "array_type,time,element_size" > "./data/heapsort_results.csv"
for i in {1..5}
do
    ./"heapsortMono"
    ./"heapsortSliced"
    ./"heapsortSQ"
done

make "matrixmult_test"
echo "array_type,time,element_size" > "./data/matrixmult_results.csv"
for i in {1..5}
do
    ./"matrixmultMono"
    ./"matrixmultSliced"
    ./"matrixmultSQ"
done