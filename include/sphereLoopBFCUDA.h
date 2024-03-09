#ifndef SPHERE_LOOP_BF_CUDA_H
#define SPHERE_LOOP_BF_CUDA_H

#include "utils.h"

using namespace std;


__global__ 
void cudaInitArr(int*, int, int, float, float, float);
set<vector<string>> loopSphereBruteForceCUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceCUDA(float , float);


#endif
