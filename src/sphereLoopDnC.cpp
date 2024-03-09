#include "sphereLoopDnC.h"

using namespace std;

set<vector<string>> loopSphere(float radius, float resolution)
{
    return loopSphere(radius, resolution, false);
}

set<vector<string>> loopSphere(float radius, float resolution, bool debug = false)
{
    std::vector<std::vector<int>> OCTANTS = {
        {1,1,+1}, {-1,1,+1}, {-1,-1,+1}, {1,-1,+1},
        {1,1,-1}, {-1,1,-1}, {-1,-1,-1}, {1,-1,-1}
    };
    std::set<std::vector<std::string>> RECURSION_SET;

    RECURSION_SET.clear();
    auto timeStart = timeMillisecond();
    set<vector<string>> re;
    if (radius <= 0) {
        return re;
    }

    if (resolution > radius) {
        resolution = radius;
    }

    float limitSquareMax = radius + resolution;
    float limitSquareMin = radius - resolution;

    int len = int(radius / resolution);
    for (int i = 0; i < len+1; i++) {
        float i_z = i * resolution;
        float i_x = len * resolution;
        while (i_x >= i_z) {
            float i_y = 0.0;
            while (i_x >= i_y) {
                float s = sumSquare(i_x, i_y, i_z);
                if ((s >= limitSquareMin) && (s <= limitSquareMax)) {
                    RECURSION_SET.insert( vector<string> {f2s(i_x), f2s(i_y), f2s(i_z)});
                    RECURSION_SET.insert( vector<string> {f2s(i_y), f2s(i_x), f2s(i_z)});
                    RECURSION_SET.insert( vector<string> {f2s(i_z), f2s(i_y), f2s(i_x)});
                }
                i_y += resolution;
            }
            i_x -= resolution;
        }
    }

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
    cout << "Duration (ms) [function: loopSphere]: " << timeDuration << endl; 
    return re;
}

