#!/bin/bash



for alg in ascgen randgen lcs
do 
    g++ ${alg}.cpp -g  -o bin/$alg
done

for alg in queue heapsort
do 
    g++ ${alg}.cpp -g -o bin/$alg
done