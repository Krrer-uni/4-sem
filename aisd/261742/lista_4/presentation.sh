#!/bin/bash

START=5
STEP=5
END=15
m=3

# rm plot/*.csv
N=10

for alg in  bst rbt splay
do
    echo "test for $alg"
    g++ ${alg}.cpp -o bin/$alg
    # cat ${alg}.cpp
            ./bin/randgen $N | ./bin/$alg
            ./bin/ascgen $N | ./bin/$alg
done
