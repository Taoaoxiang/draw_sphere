#ifndef SPHERE_LOOP_BF_H
#define SPHERE_LOOP_BF_H

#include "utils.h"

using namespace std;




// set<vector<string>> loopSphereBruteForce(float radius, float resolution, bool debug = false)
set<vector<string>> loopSphereBruteForce(float, float, bool);
set<vector<string>> loopSphereBruteForce(float, float);

void cpuInitArr(int* , int , int , float , float , float );
void cpuInitArrAll(int* , float*, int , int , float , float , float );


set<vector<string>> loopSphereBruteForceAll(float, float, bool);
set<vector<string>> loopSphereBruteForceAll(float, float);

#endif

