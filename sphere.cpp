#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <set>
#include <vector>
#include <iomanip>
#include <sstream>

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

auto timeMillisecond()
{
    using namespace chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

inline float sumSquare(float a, float b, float c)
{
    float re = (a * a) + (b * b) + (c * c);
    return re;
}

inline string f2s(float x, int precision = 3) 
{
    return number2string<float>(x, precision);
}

template <typename T> inline string number2string(T x, int precision)
{
    stringstream re;
    re << fixed << setprecision(precision) << setw(8) << x;
    return re.str();
}

inline vector<string> vF2vS(vector<float> x, int precision = 3) 
{
    return vector2vecString<float>(x, precision);
}

template <typename T> inline vector<string> vector2vecString(vector<T> x, int precision)
{
    vector<string> re;
    for (int i=0; i<x.size(); i++) {
        re.push_back(number2string<T>(x[i],precision));
    }
    return re;
}

set<vector<string>> loopSphere(float radius, float resolution, bool debug = false)
{
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
    for (int i = 0; i < len; i++) {
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

int writeToPDB(set<vector<string>> totPoints, string fname = "sphere_test_out.pdb")
{
    ofstream fo;
    fo.open(fname);
    fo << "REMARK this is a sphere\n";
    int i_ctrl = 0;
    for (set<vector<string>>::iterator p = totPoints.begin(); 
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

        fo << "ATOM " 
           << setw(6) <<  i_ctrl+1 
           << " C    DUM " << chain 
           << setw(4) << resid 
           << "    " 
           << (*p)[0]
           << (*p)[1] 
           << (*p)[2]
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
    // Time(ms): 682
    // Points: 127560
    set<vector<string>> totPoints = loopSphere(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_loop.pdb");

    // Time(ms): 14581
    // Points: 127752
    totPoints = recursionSphere(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_recursion.pdb");
    cout << "====Benchmark Finished====\n" << endl;
}

void debugTest()
{
    cout << "====Debug====" << endl;
    set<vector<string>> totPoints = loopSphere(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_loop.pdb");

    totPoints = recursionSphere(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_recursion.pdb");
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