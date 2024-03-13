#ifndef SPHERE_H
#define SPHERE_H
// #pragma once


#include "utils.h"


using namespace std;

// forward declaration
set<vector<string>> loopSphere(float, float, bool);
set<vector<string>> loopSphere(float, float);

set<vector<string>> loopSphereBruteForce(float, float, bool);
set<vector<string>> loopSphereBruteForce(float, float);

set<vector<string>> loopSphereBruteForceAll(float, float, bool);
set<vector<string>> loopSphereBruteForceAll(float, float);

set<vector<string>> loopSphereBruteForceCUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceCUDA(float , float);

set<vector<string>> loopSphereBruteForce2CUDA(float, float, bool);
set<vector<string>> loopSphereBruteForce2CUDA(float, float);

set<vector<string>> loopSphereBruteForceAllCUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceAllCUDA(float , float);

set<vector<string>> loopSphereBruteForceAll2CUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceAll2CUDA(float , float);

set<vector<string>> recursionSphere(float, float, bool);
set<vector<string>> recursionSphere(float, float);



#endif
