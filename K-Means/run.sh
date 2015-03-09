#!/bin/bash 

g++ -o cluster kmeans.cpp 
./cluster < in > results 

