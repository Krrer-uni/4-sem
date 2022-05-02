#!/bin/bash

START=100
END=10000
m=3

# rm plot/*.csv

alg=select
echo "test for $alg"
g++ ${alg}.cpp -o $alg
for N in $(seq $START 100 $END) 
do
    it=$(( $N / 10 ))
    for K in $( seq 1 $it $N)
    do
        for M in  $( seq 1 1 100 )
        do
            mydata=`./randgen $N $K | ./$alg`
            echo $mydata >> "plot/${alg}_for_${N}_${K}.csv"
        done
        cat "plot/${alg}_for_${N}_${K}.csv" | awk 'BEGIN { FS = ";" } ; {for (i=1;i<=NF;i++){a[i]+=$i;}} END {for (i=1;i<=NF;i++){printf "%.0f", a[i]/NR; printf ";"};printf "\n"}' >> "plot/${alg}9_for_${N}.csv"
        rm "plot/${alg}_for_${N}_${K}.csv"
    done
done

