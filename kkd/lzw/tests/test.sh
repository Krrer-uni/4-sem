#!/bin/bash

cp ../cmake-build-debug/decode ./
cp ../cmake-build-debug/encode ./

for test in pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt test1.bin test2.bin test3.bin
do
    for alg in 1 2 3 4
    do
        echo kodowanie $test algorytm \#${alg}
        ./encode $test $alg
        ./decode ${test}.smoll
        echo diff $test d_$test
        diff $test d_$test
    done
done

# test=test1.bin
# alg=3

#         ./encode $test $alg
#         ./decode ${test}.smoll