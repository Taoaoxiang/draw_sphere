#ifndef COMMON_H
#define COMMON_H
// #pragma once

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

// if the compiler is nvcc
#ifdef __CUDACC__
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#endif


#endif