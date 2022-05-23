#!/bin/bash



for alg in bst ascgen randgen rbt splay
do 
    g++ ${alg}.cpp -o bin/$alg
done