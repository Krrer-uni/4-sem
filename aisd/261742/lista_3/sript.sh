#!/bin/bash

START=100
END=1000

rm plot/*.csv

for alg in randselect select
do
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
            cat "plot/${alg}_for_${N}_${K}.csv" | awk 'BEGIN { FS = ";" } ; {for (i=1;i<=NF;i++){a[i]+=$i;}} END {for (i=1;i<=NF;i++){printf "%.0f", a[i]/NR; printf ";"};printf "\n"}' >> "plot/${alg}_for_${N}.csv"
            rm "plot/${alg}_for_${N}_${K}.csv"
        done

    done
done

g++ binarysearch.cpp -o binarysearch

START=1000
END=100000
echo "test for binarysearch"
for N in $(seq $START 1000 $END) 
do
    echo "test for binarysearch $N"
    it=$(( $N / 100 ))
    for K in $( seq 1 $it $(( $N + 1 )) )
    do
        mydata=`./ascgen $N $K | ./binarysearch`
        echo $mydata >> "plot/binary_for_${N}.csv"
    done
    mydata=`./ascgen $N $(( $N + 1 )) | ./binarysearch`
    echo $mydata >> "plot/binary_for_${N}.csv"
done