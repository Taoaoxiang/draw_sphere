#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

set<vector<float>> RECURSION_SET;
vector<vector<int>> OCTANTS = {
    {1,1,+1}, {-1,1,+1}, {-1,-1,+1}, {1,-1,+1},
    {1,1,-1}, {-1,1,-1}, {-1,-1,-1}, {1,-1,-1}
};

auto timeMillisecond()
{
    using namespace chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

float sumSquare(float a, float b, float c)
{
    float re = (a * a) + (b * b) + (c * c);
    return re;
}

set<vector<float>> loopSphere(float radius, float resolution, bool debug = false)
{
    auto timeStart = timeMillisecond();
    set<vector<float>> re;
    if (radius <= 0) {
        return re;
    }

    if (resolution > radius) {
        resolution = radius;
    }

    float limitSquareMax = radius + resolution;
    float limitSquareMin = radius - resolution;

    int len = int(radius / resolution);
    for (int i = 0; i < len; i++) {
        float i_z = i * resolution;
        float i_x = len * resolution;
        while (i_x >= i_z) {
            float i_y = 0.0;
            while (i_x >= i_y) {
                float s = sumSquare(i_x, i_y, i_z);
                if ((s >= limitSquareMin) && (s <= limitSquareMax)) {
                    RECURSION_SET.insert( vector<float> {i_x, i_y, i_z});
                    RECURSION_SET.insert( vector<float> {i_y, i_x, i_z});
                    RECURSION_SET.insert( vector<float> {i_z, i_y, i_x});
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
            for (set<vector<float>>::iterator p = RECURSION_SET.begin(); 
                 p!= RECURSION_SET.end(); p++) 
            {
                re.insert(vector<float> {(*s)[0]*(*p)[0], (*s)[1]*(*p)[1], (*s)[2]*(*p)[2]});
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


int writeToPDB(set<vector<float>> totPoints, string fname = "sphere_test_out.pdb")
{
    ofstream fo;
    fo.open(fname);
    fo << "REMARK this is a sphere\n";
    int i_ctrl = 0;
    for (set<vector<float>>::iterator p = totPoints.begin(); 
         p!= totPoints.end(); p++) 
    {
        int resid = i_ctrl+1;
        if (resid > 9999) {
            resid = resid % 10000;
        }
        string chain = "A";
        if ((*p).size() < 4) {
            chain = "A";
        } else {
            chain = (*p)[3];
        }
        float x = (*p)[0];
        float y = (*p)[1];
        float z = (*p)[2];

        fo << "ATOM " 
           << setw(6) <<  i_ctrl+1 
           << " C    DUM " << chain 
           << setw(4) << resid 
           << "    " 
           << fixed << setprecision(3) << setw(8) << x 
           << fixed << setprecision(3) << setw(8) << y 
           << fixed << setprecision(3) << setw(8) << z 
           << "  1.00  0.00  " << endl;
        i_ctrl += 1;
    }
    fo << "TER\n" ;
    fo.close();
    return 0;
}

void benchmarkTest()
{
    cout << "====Benchmark====" << endl;
    // Time(ms): 187
    // Points: 126678
    set<vector<float>> totPoints = loopSphere(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_loop.pdb");
    cout << "====Benchmark Finished====\n" << endl;
}

void debugTest()
{
    cout << "====Debug====" << endl;
    set<vector<float>> totPoints = loopSphere(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_loop.pdb");
    cout << "====Debug Finished====\n" << endl;
}

int main(int argc, char **argv)
{
    auto timeStart = timeMillisecond();
    debugTest();
    benchmarkTest();
    auto timeDuration = timeMillisecond() - timeStart;
    cout << "Runtime (ms): " << timeDuration << endl; 
    return 0;
}