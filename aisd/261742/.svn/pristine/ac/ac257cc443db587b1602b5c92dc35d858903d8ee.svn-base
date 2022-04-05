#!/bin/bash

cat presentation.sh

for alg in merge quick insert dpquick hybrid
do
    g++ ${alg}.cpp -o $alg
    cat ${alg}.cpp
    for alg2 in randgen descgen ascgen
    do
        for N in 8 16 32
        do
            echo " ./$alg2 $N | ./$alg "
            ./$alg2 $N | ./$alg
            echo
        done
    done
done

