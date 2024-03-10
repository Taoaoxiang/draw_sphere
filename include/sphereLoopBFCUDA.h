#ifndef SPHERE_LOOP_BF_CUDA_H
#define SPHERE_LOOP_BF_CUDA_H

#include "utils.h"

using namespace std;


__global__ 
void cudaInitArr(int*, int, int, float, float, float);
set<vector<string>> loopSphereBruteForceCUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceCUDA(float , float);

__global__ 
void cudaInitArr(int*, float*, int, int, float, float, float);
set<vector<string>> loopSphereBruteForce2CUDA(float, float, bool);
set<vector<string>> loopSphereBruteForce2CUDA(float, float);

__global__ 
void cudaInitArrAll(int*, float*, int, int, float, float, float);
set<vector<string>> loopSphereBruteForceAllCUDA(float, float, bool);
set<vector<string>> loopSphereBruteForceAllCUDA(float, float);

#endif
