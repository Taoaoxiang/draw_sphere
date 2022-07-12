#!/bin/bash

#g++ -std=c++2a -I./include src/sphere.cpp -o sphere.out
#./sphere.out
nvcc -I./include src/sphere.cu -o sphere_cu.out
./sphere_cu.out
