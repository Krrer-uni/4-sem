#!/bin/bash

rm plot/*.csv

alg=merge
for alg in quick dpquick quick_select dpquick_select
do
    g++ ${alg}.cpp -o $alg
    for N in 100 200 300 400 500 600 700 800 900 1000
    do
        for K in {1..100}
        do
            mydata=`./randgen $N | ./$alg`
            echo $mydata >> "plot/${alg}_for_${N}.csv"
            ascdata=`./ascgen $N | ./$alg`
            echo $ascdata >> "plot/${alg}_for_${N}_asc.csv"
        done
    done
done