#include "sphereRecursion.h"

using namespace std;

std::vector<std::vector<int>> OCTANTS = {
    {1,1,+1}, {-1,1,+1}, {-1,-1,+1}, {1,-1,+1},
    {1,1,-1}, {-1,1,-1}, {-1,-1,-1}, {1,-1,-1}
};
std::set<std::vector<std::string>> RECURSION_SET;

set<vector<string>> recursionSphere(float radius, float resolution) 
{
    return recursionSphere(radius, resolution, false);
}


set<vector<string>> recursionSphere(float radius, float resolution, bool debug = false)
{
    RECURSION_SET.clear();
    auto timeStart = timeMillisecond();
    set<vector<string>> re;

    float limitSquareMax = radius + resolution;
    float limitSquareMin = radius - resolution;

    vector<float> p0 = {radius, 0.0, 0.0};
    recursionSphere(p0, radius, resolution, limitSquareMin, limitSquareMax);
    
    if (!debug) {
        for (vector<vector<int>>::iterator s = OCTANTS.begin(); 
             s != OCTANTS.end(); s++) 
        {
            for (set<vector<string>>::iterator p = RECURSION_SET.begin(); 
                 p!= RECURSION_SET.end(); p++) 
            {
                vector<string> vec = {  f2s( (*s)[0] * stof( (*p)[0] ) ), 
                                        f2s( (*s)[1] * stof( (*p)[1] ) ), 
                                        f2s( (*s)[2] * stof( (*p)[2] ) )};
                re.insert(vec);
            }
        }
    } else {
        re = RECURSION_SET;
    }

    cout << re.size() << endl; 
    auto timeDuration = timeMillisecond() - timeStart;
    cout << "Duration (ms) [function: recursionSphere]: " << timeDuration << endl; 
    return re;
}

void recursionSphere(vector<float> p, float r, float resolution, float min, float max)
{
    if (p[0]<0 || p[1]<0 || p[2]<0 || p[0]>r || p[1]>r || p[2]>r) {
        return;
    }
    float s = sumSquare(p[0], p[1], p[2]);
    if ((s >= min) && (s <= max)) {
        RECURSION_SET.insert(vF2vS(p));
    }

    for (int i = 0; i < 3; i++) {
        vector<float> p1 = p;
        p1[i] = p[i] + resolution;
        if ((s <= max) && !(RECURSION_SET.find(vF2vS(p1)) != RECURSION_SET.end())) {
            recursionSphere(p1, r, resolution, min, max);
        }
        p1 = p;
        p1[i] = p[i] - resolution;
        if ((s >= min) && !(RECURSION_SET.find(vF2vS(p1)) != RECURSION_SET.end())) {
            recursionSphere(p1, r, resolution, min, max);
        }
    }

    return;
}
