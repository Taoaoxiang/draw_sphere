#!/bin/bash


mkdir -p build

g++ -c -std=c++17 -I./include -o build/utils.o src/utils.cpp

g++ -c -I./include -o build/sphereLoopDnC.o  src/sphereLoopDnC.cpp 

g++ -c -I./include -o build/sphereLoopBF.o  src/sphereLoopBF.cpp

g++ -c -I./include -o build/sphereRecursion.o  src/sphereRecursion.cpp

nvcc -c -I./include -o build/sphereLoopBFCUDA.o  src/sphereLoopBFCUDA.cu


objs="build/sphereLoopDnC.o build/utils.o build/sphereLoopBF.o build/sphereRecursion.o build/sphereLoopBFCUDA.o"

nvcc -I./include --std c++17 -o main.out  \
    ${objs} main.cpp 

./main.out