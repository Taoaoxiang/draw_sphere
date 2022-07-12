#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <set>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

set<vector<string>> RECURSION_SET;
vector<vector<int>> OCTANTS = {
    {1,1,+1}, {-1,1,+1}, {-1,-1,+1}, {1,-1,+1},
    {1,1,-1}, {-1,1,-1}, {-1,-1,-1}, {1,-1,-1}
};

auto timeMillisecond();
inline float sumSquare(float, float, float);
inline string f2s(float, int);
template <typename T> inline string number2string(T, int);
inline vector<string> vF2vS(vector<float>, int);
template <typename T> inline vector<string> vector2vecString(vector<T>, int);

set<vector<string>> loopSphere(float, float, bool);
set<vector<string>> recursionSphere(float, float, bool);
void recursionSphere(vector<float>, float, float, float, float);
int writeToPDB(set<vector<string>>, string);
__global__ void initArr(int*, int, int, float, float, float);
