#include "sphere.h"

using namespace std;

void benchmarkTest()
{
    cout << "====Benchmark====" << endl;
    // Time(ms): 682
    // Points: 127560
    set<vector<string>> totPoints;
    totPoints = loopSphere(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_loop_DnC.pdb");

    // Time(ms): 14581
    // Points: 127752
    // totPoints = recursionSphere(1.0, 0.01);
    // writeToPDB(totPoints, "benchmark_recursion.pdb");

    // Time(ms): 490
    // Points: 127840
    totPoints = loopSphereBruteForceCUDA(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_loop_BF_CUDA.pdb");

    // Time(ms): 506
    // Points: 127856
    totPoints = loopSphereBruteForce(1.0, 0.01);
    writeToPDB(totPoints, "benchmark_loop_BF.pdb");

    cout << "====Benchmark Finished====\n" << endl;
}


void debugTest()
{
    cout << "====Debug====" << endl;   
    set<vector<string>> totPoints;

    totPoints = loopSphereBruteForceCUDA(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_loop_BF_CUDA.pdb");

    totPoints = loopSphereBruteForce(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_loop_BF.pdb");
    
    totPoints = loopSphere(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_loop.pdb");

    totPoints = recursionSphere(1.0, 0.01, true);
    writeToPDB(totPoints, "debug_recursion.pdb");
    cout << "====Debug Finished====\n" << endl;
}

int main(int argc, char **argv)
{
    auto timeStart = timeMillisecond();

    debugTest();
    // benchmarkTest();

    auto timeDuration = timeMillisecond() - timeStart;
    cout << "Runtime (ms): " << timeDuration << endl; 
    return 0;
}