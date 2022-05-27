#!/bin/bash

START=10000
STEP=10000
END=100000
m=3

# rm plot/*.csv


for alg in splay rbt bst
do
    echo "test for $alg"
    g++ ${alg}.cpp -o bin/$alg
    for N in $(seq $START $STEP $END) 
    do
        echo $N
        rm "data/${alg}_for_${N}_rand.csv"
        rm "data/${alg}_for_${N}_asc.csv"
        for M in  $( seq 1 1 20 )
        do
            mydata=`./bin/randgen $N | ./bin/$alg`
            echo $mydata >> "data/${alg}_for_${N}_rand.csv"
            mydata=`./bin/ascgen $N | ./bin/$alg`
            echo $mydata >> "data/${alg}_for_${N}_asc.csv"
        done
    done
done
