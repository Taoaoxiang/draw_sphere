all: sphere

sphere: prepare main

prepare:
	mkdir -p $(BUILD) $(BIN)

clean: 
	rm -f $(BUILD)/*.o $(BIN)/*

# define the compiler
CC = g++
NVCC = nvcc

# define any compile-time flags
CFLAGS = -Wall -g -std=c++2a -O3
NVCCFLAGS = -O3 --std c++17

# define any directories containing header files other than /usr/include
INCLUDES = -I./include 
BUILD=./build
SOURCE=./src
BIN=./bin
OBJS=$(BUILD)/utils.o \
	$(BUILD)/sphereLoopDnC.o \
	$(BUILD)/sphereLoopBF.o \
	$(BUILD)/sphereRecursion.o \
	$(BUILD)/sphereLoopBFCUDA.o

# utils.o
$(BUILD)/utils.o: $(SOURCE)/utils.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE)/utils.cpp -o $(BUILD)/utils.o

# sphereLoopDnC.o
$(BUILD)/sphereLoopDnC.o : $(SOURCE)/sphereLoopDnC.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE)/sphereLoopDnC.cpp -o $(BUILD)/sphereLoopDnC.o

# sphereLoopBF.o
$(BUILD)/sphereLoopBF.o : $(SOURCE)/sphereLoopBF.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE)/sphereLoopBF.cpp -o $(BUILD)/sphereLoopBF.o

# sphereRecursion.o
$(BUILD)/sphereRecursion.o : $(SOURCE)/sphereRecursion.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE)/sphereRecursion.cpp -o $(BUILD)/sphereRecursion.o

# sphereLoopBFCUDA.o
$(BUILD)/sphereLoopBFCUDA.o : $(SOURCE)/sphereLoopBFCUDA.cu
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) -c $(SOURCE)/sphereLoopBFCUDA.cu -o $(BUILD)/sphereLoopBFCUDA.o

main: $(OBJS)
	$(NVCC) $(NVCCFLAGS) $(INCLUDES) $(OBJS) -o $(BIN)/sphere main.cpp
	$(BIN)/sphere

