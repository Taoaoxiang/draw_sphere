#include "sphereLoopBFCUDA.h"

using namespace std;

__global__ 
void cudaInitArr(int* arr, 
                 int ROW, 
                 int len, 
                 float resolution, 
                 float max, float min)
{
    // int i = threadIdx.x;
    int index = threadIdx.x;
    int stride = blockDim.x;

    for (int i = index; i < ROW; i+=stride) {
        // 1. grows in z direction, from 0 to len
        float z = float( i % (len+1))                   * resolution;
        // 2. grows in y direction, from 0 to len
        float y = float( i/(len+1) % (len+1))           * resolution;
        // 3. grows in x direction, from 0 to len
        float x = float( i/((len+1)*(len+1)) % (len+1)) * resolution;
        // float y = float( (i%((len+1)*(len+1))) / (len+1)) * resolution;
        
        float sum = (x*x)+(y*y)+(z*z);
        if (sum>=min && sum<=max) {
            arr[i] = 1;
        } else {
            arr[i] = 0;
        }
    }
}

set<vector<string>> loopSphereBruteForceCUDA(float radius, float resolution)
{
    return loopSphereBruteForceCUDA(radius, resolution, false);
}


set<vector<string>> loopSphereBruteForceCUDA(float radius, float resolution, bool debug = false)
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
    int ROW = (len + 1) * (len + 1) * (len + 1); 
    int   *intArr,   *gpu_intArr;

    
    #define BLOCK_SIZE 256
    #define GRID_SIZE 100

    intArr = (int*)malloc(sizeof(int) * ROW);
    cudaMalloc((void**)&gpu_intArr, sizeof(int) * ROW);
    // cudaMemcpy(gpu_intArr, intArr, sizeof(int) * ROW, cudaMemcpyHostToDevice);

    cudaInitArr<<<GRID_SIZE, BLOCK_SIZE>>>
        (gpu_intArr, ROW, len, resolution, limitSquareMax, limitSquareMin);
    cudaMemcpy(intArr, gpu_intArr, sizeof(int) * ROW, cudaMemcpyDeviceToHost);

    for (int i = 0; i < ROW; i++) {
        if (intArr[i] == 1) {
            float z = resolution * (i % (len + 1));
            float y = resolution * (i/(len+1) %(len+1));
            float x = resolution * (i/((len+1)*(len+1)) % (len+1));
            RECURSION_SET.insert( vector<string> {f2s(x), f2s(y), f2s(z)});
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
    cout << "Duration (ms) [function: loopSphereBruteForceCUDA]: " << timeDuration << endl; 
    return re;
}

