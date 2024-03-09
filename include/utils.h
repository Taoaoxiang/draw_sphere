#ifndef UTILS_H
#define UTILS_H

#include "common.h"

using namespace std;

unsigned long timeMillisecond();
float sumSquare(float, float, float);
string f2s(float, int);
string f2s(float);
template <typename T> string number2string(T, int);
vector<string> vF2vS(vector<float>); 
vector<string> vF2vS(vector<float>, int);
template <typename T> vector<string> vector2vecString(vector<T>, int);

int writeToPDB(set<vector<string>>, string);


#endif