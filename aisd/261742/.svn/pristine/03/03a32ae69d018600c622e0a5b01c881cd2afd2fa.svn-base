#!/bin/bash

alg=merge
for alg in merge quick insert dpquick hybrid
do
    g++ ${alg}.cpp -o $alg
    for N in 100 200 300 400 500 600 700 800 900 1000
    do
        for K in {1..100}
        do
            mydata=`./randgen $N | ./$alg`
            echo $mydata >> "plot/${alg}_for_${N}_.csv"
        done
    done
done