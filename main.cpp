#include "sphere.h"

using namespace std;

void benchmarkTest()
{
    cout << "====Benchmark====" << endl;
    set<vector<string>> totPoints;

    string dir = "output";

    if (!filesystem::is_directory(dir) || !filesystem::exists(dir)) { 
        filesystem::create_directory(dir); 
    }

    string pdb;

    // Time(ms): 682
    // Points: 127560
    // totPoints = loopSphere(1.0, 0.01);
    // writeToPDB(totPoints, "benchmark_loop_DnC.pdb");

    // Time(ms): 14581
    // Points: 127752
    // totPoints = recursionSphere(1.0, 0.01);
    // writeToPDB(totPoints, "benchmark_recursion.pdb");

    // Time(ms): 490
    // Points: 127840
    totPoints = loopSphereBruteForceCUDA(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BF_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    // Time(ms): 506
    // Points: 127856
    totPoints = loopSphereBruteForce(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BF.pdb";
    writeToPDB(totPoints, pdb);

    // Time(ms): 492
    // Points: 127840
    totPoints = loopSphereBruteForce2CUDA(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BF2_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    // Time(ms): 516
    // Points: 125914
    totPoints = loopSphereBruteForceAllCUDA(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BFAll_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    // Time(ms): 503
    // Points: 125914
    totPoints = loopSphereBruteForceAll2CUDA(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BFAll2_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    // Time(ms): 518
    // Points: 125930
    totPoints = loopSphereBruteForceAll(1.0, 0.01);
    pdb = dir + "/" + "benchmark_loop_BFAll.pdb";
    writeToPDB(totPoints, pdb);
    

    cout << "====Benchmark Finished====\n" << endl;
}


void debugTest()
{
    cout << "====Debug====" << endl;   
    set<vector<string>> totPoints;

    string dir = "output";

    if (!filesystem::is_directory(dir) || !filesystem::exists(dir)) { 
        filesystem::create_directory(dir); 
    }

    string pdb;

    totPoints = loopSphereBruteForceCUDA(1.0, 0.01, true);
    pdb = dir + "/" + "debug_loop_BF_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    totPoints = loopSphereBruteForce(1.0, 0.01, true);
    pdb = dir + "/" + "debug_loop_BF.pdb";
    writeToPDB(totPoints, pdb);
    
    totPoints = loopSphereBruteForce2CUDA(1.0, 0.01, true);
    pdb = dir + "/" + "debug_loop_BF2_CUDA.pdb";
    writeToPDB(totPoints, pdb);

    // totPoints = loopSphere(1.0, 0.01, true);
    // pdb = dir + "/" + "debug_loop_DnC.pdb";
    // writeToPDB(totPoints, pdb);

    // totPoints = recursionSphere(1.0, 0.01, true);
    // pdb = dir + "/" + "debug_recursion.pdb";
    // writeToPDB(totPoints, pdb);

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