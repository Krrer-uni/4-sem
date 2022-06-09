#!/bin/bash

cat presentation.sh

for alg in select randselect
do
    g++ ${alg}.cpp -o $alg
    cat ${alg}.cpp
    for alg2 in randgen 
    # descgen ascgen
    do
        for N in 8 16 32
        do
            for K in 1 $(( $N / 2 )) $N
            do
               echo " ./$alg2 $N  $K | ./$alg "
                ./$alg2 $N $K | ./$alg
               echo
            done
        done
    done
done

