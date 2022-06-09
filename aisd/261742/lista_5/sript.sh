#!/bin/bash

rm plot/*.csv

alg=merge
for alg in heapsort queue
do
    echo $alg
    g++ ${alg}.cpp -o $alg
    for N in 100 200 300 400 500 600 700 800 900 1000
    do
        for K in {1..100}
        do
            mydata=`./bin/randgen $N | ./bin/$alg`
            echo $mydata >> "plot/${alg}_for_${N}.csv"
        done
    done
done

alg=lcs
g++ ${alg}.cpp -o $alg
for N in 1000 2000 3000 4000 5000
do
    for K in {1..100}
    do
        mydata=`./bin/$alg $N 32`
        echo $mydata >> "plot/${alg}_for_${N}.csv"
    done
done