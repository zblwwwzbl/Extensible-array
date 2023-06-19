# Extensive Array

Research project on Extensive Arrays, as a part of the undergraduate subject COMP30013 in the University of Melbourne. 

## Usage

The repository contains 5 array implementation: monolithic array (monolithic.c), sliced array (sliced.c), SQarray (SQarray.c), HAT (HAT.c), geometric array (geometric.c) and multisliced array (multisliced.c).

The complilation logic can be find in the Makefile. Usually, make requires 3 additional arguments
    * target: the test_name
    * SIZE: the element size (for the base array, this is the size of the payload)
    * R: the R parameter for the multisliced array
e.g.
```bash
make target=sort SIZE=32 R=3
```

### Running experiments
The majority of the experiments could be ran using the 
```bash
./run_test.sh <test_name> 
```
The test_name of the experiments performed in the report are:
    * Experiment A: make_space
    * Experiment B: insert
    * Experiment C: insert_length
    * Experiment D: insert_space
    * Experiemtn E: random_access
    * Experiment F: reverse
    * Experiment G: sort
    * Experiment H: heapsort
    * Unused experiment: matrixmult (matrix multiplication), incone (increasing the key of every element by one)

To run experiment C, comment out line 26,27 in the Makefile and uncomment line 29,30, then run
```bash
./run_insert_length.sh insert_length
```

To run experiment D or E, use
```bash
./run_make_space.sh make_space
./run_random_access.sh random_access
```

### Analysing results
The test results are stored in the data file, in CSV format (except experiment D which produces txt). To analyze the results, go to analysis.ipynb, in the second cell, change the type variable to the experiment you want to analyze
` type = <test_name> `
And then run cell 3. 

## Additional note
* The base array is implemented poorly. It requries significant changes if you want the base array to work in the insert_length test
* The file run_intel_test.sh is used to produce the result of random_access on a Intel i5 CPU computer
* The general logic of the dope vector is implemented in general.c and general.h