#!/bin/bash

for test in pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt test1.bin test2.bin test3.bin
do
    for alg in 1 2 3 4
    do
        ./encode $test $alg
        ./decode ${test}.smoll
        echo diff $test d_$test
        diff $test d_$test
    done
done