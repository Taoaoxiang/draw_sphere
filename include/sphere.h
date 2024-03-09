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

set<vector<string>> loopSphereBruteForceCUDA(float , float , bool);
set<vector<string>> loopSphereBruteForceCUDA(float , float);


set<vector<string>> recursionSphere(float, float, bool);
set<vector<string>> recursionSphere(float, float);



#endif
