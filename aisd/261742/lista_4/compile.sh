#!/bin/bash



for alg in bst ascgen randgen
do 
    g++ ${alg}.cpp -o bin/$alg
done