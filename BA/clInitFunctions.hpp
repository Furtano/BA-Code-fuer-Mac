#ifndef CLFUNC
#define CLFUNC


#include "Globals.h"



#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

class openCLinit {
public:
	cl_program program;
	cl_program program2;
	void antcl ();
	openCLinit();
	void print_cl_err(int err_code);
	void getDeviceInfos ();
	cl_context CreateContext();
	cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device);
	cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName);
	bool CreateMemObjects(cl_context context, cl_mem memObjects[3],
						  float *a, float *b);


	//void Cleanup(cl_context context, cl_command_queue commandQueue,
	//			 cl_program program, cl_kernel kernel, cl_mem memObjects[10]);
    int startOpenCLmain();
	void CleanupEnd();
	int initiate ();
	cl_mem memObjects[12];
	cl_mem memObjects2[7];
	cl_context context;
	cl_command_queue commandQueue;
	size_t globalWorkSize[1];
	size_t localWorkSize[1];
	cl_kernel kernel;
	cl_kernel kernel2;
	// Number of Ants
	bool targetArrived[ARRAY_SIZE];
	float resultX[ARRAY_SIZE];
	float resultY[ARRAY_SIZE];
	float world[ARRAY_SIZE];
	float antX[ARRAY_SIZE];
	float antY[ARRAY_SIZE];
	int targetX[ARRAY_SIZE];
	int targetY[ARRAY_SIZE];
	float newAntX[ARRAY_SIZE];
	float newAntY[ARRAY_SIZE];
	int direction[ARRAY_SIZE];
	int speed[ARRAY_SIZE];
	int color[ARRAY_SIZE];
	int lifeStadium[ARRAY_SIZE];
	bool isCarryingFood[ARRAY_SIZE];

	int pheromonEuter[ARRAY_SIZE];

	float pheromonX[ARRAY_SIZE];
	float pheromonY[ARRAY_SIZE];
	float pheromonNewX[ARRAY_SIZE];
	float pheromonNewY[ARRAY_SIZE];
	int mode[ARRAY_SIZE];

	// contains Pheromons and Food
	// Pheromon values between 0-10, Food Values between 100-300
	int pheromonMap[WIDTH*HEIGHT];

	float viewSize;
	int moveX;
	int moveY;
};
#endif
