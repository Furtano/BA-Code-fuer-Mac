
#include "Globals.h"
#include "clInitFunctions.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <String>
#include "Helper.h"

const char * antclpath = "/Users/Chris/Desktop/uni/8_semester/BA Code fuer Mac/BA/Ant.cl";
const char * pheromonpath = "/Users/Chris/Desktop/uni/8_semester/BA Code fuer Mac/BA/Pheromon.cl";

int getPheromonMapID (int x, int y){
	int w = 800;

	return y*w+x;
}
float lenghtOfVector (float x, float y){

	return sqrt(x*x + y*y);
}

openCLinit::openCLinit(){
	
viewSize = 1.0;
 moveX = 0;
 moveY = 0;
	initiate();
#pragma omp parallel 
	{
		#pragma omp for 
		for (int i = 0; i < WIDTH*HEIGHT; i++){
			pheromonMap[i] = 0;
		}
	}

#pragma omp parallel 
{
	#pragma omp for 
		for (int i = 0; i < ARRAY_SIZE; i++)
		{

			pheromonEuter[i] = 800;
			pheromonX[i] = -1;
			pheromonY[i] = -1;
			pheromonNewX[i] = -1;
			pheromonNewY[i] = -1;




			isCarryingFood[i] = false;
			world[i] = 0;
			speed[i] = Helper::getRandomInt(5,1);
			//speed[i] = 1;
			direction[i] = 0;

			// Ant Postition == Parallelisierbar ???
			antX[i] = STARTPOSX;
			antY[i] = STARTPOSY;


			targetX[i] = 0;
			targetY[i] = 0;

			newAntX[i] = 0;
			newAntY[i] = 0;
			resultX[i] = 0;
			resultX[i] = 0;
			color[i] = 0;
			lifeStadium[i] = 0;

		}
	}

	for (int i = 0; i < startPopulation; i++){
		lifeStadium[i] = 1;
	}

#pragma omp parallel 
	{
#pragma omp for 
		for (int i =0; i < ARRAY_SIZE; i++){
			int randomm = 0;
			do {

				randomm =  Helper::getRandomInt(WIDTH, 0);

			}
			while (targetX[i] == randomm);
			//std::cout << init->targetX[i] << std::endl;
			targetX[i] = randomm;

			do {

				randomm = Helper::getRandomInt(WIDTH, 0);
			}
			while (targetY[i] == randomm);

			targetY[i] = randomm;


		}
	}

	
}

void openCLinit::print_cl_err(int err_code)
{
	switch(err_code)
	{
	case 0:
		fprintf(stderr, "Error code: 0 CL_SUCCESS\n");
		break;
	case -1:
		fprintf(stderr, "Error code: -1 CL_DEVICE_NOT_FOUND\n");
		break;
	case -2:
		fprintf(stderr, "Error code: -2 CL_DEVICE_NOT_AVAILABLE\n");
		break;
	case -3:
		fprintf(stderr, "Error code: -3 CL_COMPILER_NOT_AVAILABLE\n");
		break;
	case -4:
		fprintf(stderr, "Error code: -4 CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
		break;
	case -5:
		fprintf(stderr, "Error code: -5 CL_OUT_OF_RESOURCES\n");
		break;
	case -6:
		fprintf(stderr, "Error code: -6 CL_OUT_OF_HOST_MEMORY\n");
		break;
	case -7:
		fprintf(stderr, "Error code: -7 CL_PROFILING_INFO_NOT_AVAILABLE\n");
		break;
	case -8:
		fprintf(stderr, "Error code: -8 CL_MEM_COPY_OVERLAP\n");
		break;
	case -9:
		fprintf(stderr, "Error code: -9 CL_IMAGE_FORMAT_MISMATCH\n");
		break;
	case -10:
		fprintf(stderr, "Error code: -10 CL_IMAGE_FORMAT_NOT_SUPPORTED\n");
		break;
	case -11:
		fprintf(stderr, "Error code: -11 CL_BUILD_PROGRAM_FAILURE\n");
		break;
	case -12:
		fprintf(stderr, "Error code: -12 CL_MAP_FAILURE\n");
		break;
	case -30:
		fprintf(stderr, "Error code: -30 CL_INVALID_VALUE\n");
		break;
	case -31:
		fprintf(stderr, "Error code: -31 CL_INVALID_DEVICE_TYPE\n");
		break;
	case -32:
		fprintf(stderr, "Error code: -32 CL_INVALID_PLATFORM\n");
		break;
	case -33:
		fprintf(stderr, "Error code: -33 CL_INVALID_DEVICE\n");
		break;
	case -34:
		fprintf(stderr, "Error code: -34 CL_INVALID_CONTEXT\n");
		break;
	case -35:
		fprintf(stderr, "Error code: -35 CL_INVALID_QUEUE_PROPERTIES\n");
		break;
	case -36:
		fprintf(stderr, "Error code: -36 CL_INVALID_COMMAND_QUEUE\n");
		break;
	case -37:
		fprintf(stderr, "Error code: -37 CL_INVALID_HOST_PTR\n");
		break;
	case -38:
		fprintf(stderr, "Error code: -38 CL_INVALID_MEM_OBJECT\n");
		break;
	case -39:
		fprintf(stderr, "Error code: -39 CL_INVALID_IMAGE_FORMAT_DESCRIPTOR\n");
		break;
	case -40:
		fprintf(stderr, "Error code: -40 CL_INVALID_IMAGE_SIZE\n");
		break;
	case -41:
		fprintf(stderr, "Error code: -41 CL_INVALID_SAMPLER\n");
		break;
	case -42:
		fprintf(stderr, "Error code: -42 CL_INVALID_BINARY\n");
		break;
	case -43:
		fprintf(stderr, "Error code: -43 CL_INVALID_BUILD_OPTIONS\n");
		break;
	case -44:
		fprintf(stderr, "Error code: -44 CL_INVALID_PROGRAM\n");
		break;
	case -45:
		fprintf(stderr, "Error code: -45 CL_INVALID_PROGRAM_EXECUTABLE\n");
		break;
	case -46:
		fprintf(stderr, "Error code: -46 CL_INVALID_KERNEL_NAME\n");
		break;
	case -47:
		fprintf(stderr, "Error code: -47 CL_INVALID_KERNEL_DEFINITION\n");
		break;
	case -48:
		fprintf(stderr, "Error code: -48 CL_INVALID_KERNEL\n");
		break;
	case -49:
		fprintf(stderr, "Error code: -49 CL_INVALID_ARG_INDEX\n");
		break;
	case -50:
		fprintf(stderr, "Error code: -50 CL_INVALID_ARG_VALUE\n");
		break;
	case -51:
		fprintf(stderr, "Error code: -51 CL_INVALID_ARG_SIZE\n");
		break;
	case -52:
		fprintf(stderr, "Error code: -52 CL_INVALID_KERNEL_ARGS\n");
		break;
	case -53:
		fprintf(stderr, "Error code: -53 CL_INVALID_WORK_DIMENSION\n");
		break;
	case -54:
		fprintf(stderr, "Error code: -54 CL_INVALID_WORK_GROUP_SIZE\n");
		break;
	case -55:
		fprintf(stderr, "Error code: -55 CL_INVALID_WORK_ITEM_SIZE\n");
		break;
	case -56:
		fprintf(stderr, "Error code: -56 CL_INVALID_GLOBAL_OFFSET\n");
		break;
	case -57:
		fprintf(stderr, "Error code: -57 CL_INVALID_EVENT_WAIT_LIST\n");
		break;
	case -58:
		fprintf(stderr, "Error code: -58 CL_INVALID_EVENT\n");
		break;
	case -59:
		fprintf(stderr, "Error code: -59 CL_INVALID_OPERATION\n");
		break;
	case -60:
		fprintf(stderr, "Error code: -60 CL_INVALID_GL_OBJECT\n");
		break;
	case -61:
		fprintf(stderr, "Error code: -61 CL_INVALID_BUFFER_SIZE\n");
		break;
	case -62:
		fprintf(stderr, "Error code: -62 CL_INVALID_MIP_LEVEL\n");
		break;
	case -63:
		fprintf(stderr, "Error code: -63 CL_INVALID_GLOBAL_WORK_SIZE\n");
		break;
	default:
		fprintf(stderr, "Unknown error code: %d\n", err_code);
		break;
	}
}


/**
*	Gibt die Geräteinformationen (Name, Hersteller) der möglichen Devices aus, die für OpenCl benutzt werden können.
*
*
**/
void openCLinit::getDeviceInfos (){
	cl_platform_id platforms[100];
	cl_uint platforms_n = 0;
	cl_uint devices_n = 0;
	char buffer[10240];
	cl_uint buf_uint;

	clGetPlatformIDs(100, platforms, &platforms_n);

	cl_device_id devices[100];
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 100, devices, &devices_n);
	for (int i=0; i< devices_n; i++)
	{
		std::cout << "DEVICE " << i << "\n";

		clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL);
		printf("  VENDOR_NAME = %s\n", buffer);

		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
		printf("  DEVICE_NAME = %s\n", buffer);

		clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, NULL);
		printf("  DEVICE_MAX_COMPUTE_UNITS = %u\n", (unsigned int)buf_uint);

		clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buf_uint), &buf_uint, NULL);
		printf("  CL_DEVICE_MAX_CLOCK_FREQUENCY	 = %u\n", (unsigned int)buf_uint);


		printf("\n");printf("\n");
	}

}

cl_context openCLinit::CreateContext()
{
	cl_int errNum;
	cl_uint numPlatforms;
	cl_platform_id platforms[100];
	cl_context context = NULL;

	// First, select an OpenCL platform to run on.  For this example, we
	// simply choose the first available platform.  Normally, you would
	// query for all available platforms and select the most appropriate one.
	errNum = clGetPlatformIDs(100, platforms, &numPlatforms);
	if (errNum != CL_SUCCESS || numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return NULL;
	}

	// Next, create an OpenCL context on the platform.  Attempt to
	// create a GPU-based context, and if that fails, try to create
	// a CPU-based context.
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		// für Rest
		(cl_context_properties)platforms[0],
		// für Nvidia
		//(cl_context_properties)platforms[1],
		0
	};
	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,
		NULL, NULL, &errNum);
	if (errNum != CL_SUCCESS)
	{
		std::cout << "!!Could not create GPU context, trying CPU..." << std::endl;
		context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
			NULL, NULL, &errNum);
		if (errNum != CL_SUCCESS)
		{
			std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
			return NULL;
		}
	}

	return context;
}

///
//  Create a command queue on the first device available on the
//  context
//
cl_command_queue openCLinit::CreateCommandQueue(cl_context context, cl_device_id *device)
{
	cl_int errNum;
	cl_device_id *devices;
	this->commandQueue = NULL;
	size_t deviceBufferSize = -1;

	// First get the size of the devices buffer
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed call to clGetContextInfo(...,GL_CONTEXT_DEVICES,...)";
		return NULL;
	}

	if (deviceBufferSize <= 0)
	{
		std::cerr << "No devices available.";
		return NULL;
	}

	// Allocate memory for the devices buffer
	devices = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, devices, NULL);
	if (errNum != CL_SUCCESS)
	{
		delete [] devices;
		std::cerr << "Failed to get device IDs";
		return NULL;
	}

	// In this example, we just choose the first available device.  In a
	// real program, you would likely use all available devices or choose
	// the highest performance device based on OpenCL device queries
	commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
	if (commandQueue == NULL)
	{
		delete [] devices;
		std::cerr << "Failed to create commandQueue for device 0";
		return NULL;
	}

	*device = devices[0];
	delete [] devices;
	return commandQueue;
}

///
//  Create an OpenCL program from the kernel source file
//
cl_program openCLinit::CreateProgram(cl_context context, cl_device_id device, const char* fileName)
{
	cl_int errNum;
	cl_program program;

	std::ifstream kernelFile(fileName, std::ios::in);
	if (!kernelFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
		return NULL;
	}

	std::ostringstream oss;
	oss << kernelFile.rdbuf();

	std::string srcStdStr = oss.str();
	const char *srcStr = srcStdStr.c_str();
	program = clCreateProgramWithSource(context, 1,
		(const char**)&srcStr,
		NULL, NULL);
	if (program == NULL)
	{
		std::cerr << "Failed to create CL program from source." << std::endl;
		return NULL;
	}

	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (errNum != CL_SUCCESS)
	{
		// Determine the reason for the error
		char buildLog[16384];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
			sizeof(buildLog), buildLog, NULL);

		std::cerr << "Error in kernel: " << std::endl;
		std::cerr << buildLog;
		clReleaseProgram(program);
		return NULL;
	}

	return program;
}




bool checkMemObjects (cl_mem *memObjects, int startAt, int size,int errorcode){
	for (int i = startAt ; i < size; i++){
		if(memObjects[i] == NULL){

			std::cerr << i << "-> Index : Error creating memory objects!!!!! ERRORCODE: " << errorcode << std::endl; 
			return false;
		}
	}
    return false;

}

bool CreateMemObjectsPheromonModeOfAnt (cl_context context, cl_mem memObjects2[7], float *x, float *y, int *pheromonMap, float *newX, float *newY, int * modus, bool* isCarryingFood){

	cl_int errorcode;

	// Input
	memObjects2[3] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, x, &errorcode);
	memObjects2[4] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, y, &errorcode);
	memObjects2[6] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(bool) * ARRAY_SIZE, isCarryingFood, &errorcode);
	// In & Output
	memObjects2[2] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * (WIDTH*HEIGHT), pheromonMap, &errorcode);
	memObjects2[5] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * (ARRAY_SIZE), modus, &errorcode);


	// Output
	memObjects2[0] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float) * ARRAY_SIZE, NULL, &errorcode);
	memObjects2[1] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float) * ARRAY_SIZE, NULL, &errorcode);




	checkMemObjects(memObjects2, 0, 6, errorcode);


	return false;

}


bool CreateMemObjectsAnts(cl_context context, cl_mem memObjects[11],
						  float *antX, float *antY,  int *targetX, int *targetY,float * resultX, float * resultY, float *newAntX, float *newAntY, int * lifeStadium, int * speed, int * mode, int * pheromons)
{
	cl_int errorcode;

	// Input

	memObjects[4] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * ARRAY_SIZE, targetX, &errorcode);
	memObjects[5] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * ARRAY_SIZE, targetY, &errorcode);
	memObjects[6] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, resultX, &errorcode);
	memObjects[7] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, resultY, &errorcode);
	memObjects[8] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
		sizeof(int) * ARRAY_SIZE, lifeStadium, &errorcode);
	memObjects[9] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * ARRAY_SIZE, speed, &errorcode);

	memObjects[10] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * ARRAY_SIZE, mode, &errorcode);
	memObjects[11] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * WIDTH*HEIGHT, pheromons, &errorcode);

	// Output
	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float) * ARRAY_SIZE, NULL, &errorcode);
	memObjects[3] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float) * ARRAY_SIZE, NULL, &errorcode);


	checkMemObjects(memObjects, 2, 10, errorcode);


	return true;
}
///
//  Cleanup any created OpenCL resources
//
//void openCLinit::Cleanup(cl_context context, cl_command_queue commandQueue,
//			 cl_program program, cl_kernel kernel, cl_mem memObjects[11])
//{
//	for (int i = 0; i < 11; i++)
//	{
//		if (memObjects[i] != 0)
//			clReleaseMemObject(memObjects[i]);
//	}


//}

void openCLinit::CleanupEnd(){
	for (int i = 0; i < 12; i++)
	{
		if (memObjects[i] != 0)
			clReleaseMemObject(this->memObjects[i]);
	}
	for (int i = 0; i < 7; i++)
	{
		if (memObjects2[i] != 0)
			clReleaseMemObject(this->memObjects2[i]);
	}

	if (commandQueue != 0)
		clReleaseCommandQueue(commandQueue);

	if (kernel != 0)
		clReleaseKernel(kernel);

	if (program != 0)
		clReleaseProgram(program);

	if (context != 0)
		clReleaseContext(context);
}

int  openCLinit::initiate (){
	std::ofstream openclLogger;
	context = 0;
	cl_command_queue commandQueue = 0;

	cl_device_id device = 0;
	kernel = 0;
	kernel2 = 0;
	for (int i = 0; i < 12; i++){
		this->memObjects[i] = 0;
	}

	cl_int errNum = 0;


	// DEBUG
	getDeviceInfos();

	// Create an OpenCL context on first available platform
	context = CreateContext();
	if (context == NULL)
	{
		print_cl_err(errNum);
		return 1;
	}



	// Create a command-queue on the first device available
	// on the created context
	commandQueue = CreateCommandQueue(context, &device);
	if (commandQueue == NULL)
	{
		print_cl_err(errNum);
		//Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

    
	// Create OpenCL program from HelloWorld.cl kernel source
	program = CreateProgram(context, device, antclpath);
	program2 = CreateProgram(context, device, pheromonpath);
	if (program == NULL || program2 == NULL)
	{
		std::cout << "PROGRAM CREATE ERROR";
		print_cl_err(errNum);
		//Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

	// Create OpenCL kernel
	kernel = clCreateKernel(program, "stepSizeAnt", &errNum);
	kernel2 = clCreateKernel(program2, "pheromon", &errNum);

	if (kernel == NULL || kernel2 == NULL)
	{
		std::cout << "KERNEL CREATE ERROR" << errNum;
		print_cl_err(errNum);
		//Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}



	if (!CreateMemObjectsAnts(context, memObjects,antX, antY,  targetX, targetY,resultX,resultY,newAntX,newAntY, lifeStadium, speed, mode, pheromonMap))
	{
		//Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

	if (CreateMemObjectsPheromonModeOfAnt(context, memObjects2, pheromonX, pheromonY, pheromonMap, pheromonNewX, pheromonNewY, mode, isCarryingFood)){
		std::cout << "ERROR MEMOBJECTS CREATE";
	}


	// Set the kernel arguments (result, a, b)

	for (int i = 0; i < 12; i++){
		std::cout << i;
		int error =  clSetKernelArg(kernel, i, sizeof(cl_mem), &memObjects[i]);
		if (error != 0)
			std::cout <<  "Kernel Args error:" << error  << std::endl;
	}

	for (int i = 0; i < 7; i++){

		int error =  clSetKernelArg(kernel2, i, sizeof(cl_mem), &memObjects2[i]);
		if (error != 0)
			print_cl_err(error);
	}

	return 0;
}

void openCLinit::antcl (){
    
#pragma omp parallel for

	for (int gid = 0; gid < ARRAY_SIZE; gid++){
		// only if Ant is living
		if (lifeStadium[gid] == 1){



			/**

			IF ANT GETS AN NEW TARGET, GO TO IT 
			WHILE SNIFFING

			**/
			// if Ant is not in PheromonMode
			if (mode[gid] != 3){
				// Neuen Richtungsvektor berechnen (in Welche Richtung soll die Ameise laufen)
				resultX[gid] = (targetX[gid]-antX[gid]);
				resultY[gid] = (targetY[gid]-antY[gid]);

				// Normvektor ausrechnen normalisieren



				float norm = lenghtOfVector(resultX[gid], resultY[gid]);

				// Richtungsvektor normalisieren
				resultX[gid] = (resultX[gid] / norm);
				resultY[gid] = (resultY[gid] / norm);

				// Ameisenschritt machen
				// neue Ameisenposition = Alte Position + (neue Schrittposition * Geschwindigkeit)
				antX[gid] +=   (resultX[gid])*speed[gid];
				antY[gid] +=   (resultY[gid])*speed[gid];

			}



			/**

			IF ANT SNIFFS
			FOLLOW THE PHEROMONS

			**/


			if(mode[gid] == 3) {

				// Temp X,Y 
				int x = antX[gid];
				int y = antY[gid];

				// RANDOM SEED
				int strongID = getPheromonMapID(antX[gid],antY[gid]);
				int strongestValue = pheromonMap[strongID];

				// FOR RADIUS XXX
				//            X X
				//            XXX
				int radius = PHERMON_SEARCH_RADIUS;
				for (int i = antY[gid]-radius-speed[gid]; i < antY[gid]+radius+speed[gid]; i++){
					for (int j = antX[gid]-radius-speed[gid]; j < antX[gid]+radius+speed[gid]; j++){

						if (i > 0 && j > 0 && i < 800 && j < 800){
							// check 1 Radius Field
							int id = getPheromonMapID(j,i);
							int checkFieldValue = pheromonMap[id];


							// found new Direction???
							if (checkFieldValue > strongestValue){
								// set new Highest
								strongestValue = checkFieldValue;
								x = j;
								y = i;
							}

						}

					}

				}

				antX[gid] =  x ;
				antY[gid] =  y ;

			}

		}
	}




}
float durchschnittsZeit = 0.0;
int anzahl = 0;
int  openCLinit::startOpenCLmain(){


	// Create memory objects that will be used as arguments to
	// kernel.  First create host memory arrays that will be
	// used to store the arguments to the kernel





	globalWorkSize[0] = ARRAY_SIZE ;
	localWorkSize[0] = 1;
    
    
    
    
    
    
    
    
    
    sf::Clock hey;
    std::string art = "";
    if (false){
        art = "CL";
        //// Write Buffer for Kernel 1
        clEnqueueWriteBuffer(commandQueue, memObjects[2], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, antX, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[3], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, antY, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[4], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, targetX, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[5], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, targetY, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[8], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, lifeStadium, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[9], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, speed, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[10], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, mode, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects[11], CL_FALSE, 0, sizeof(int) * WIDTH*HEIGHT, pheromonMap, 0, NULL, NULL);
        
        
        
        // Execute Kernel 1
        clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
                               globalWorkSize, NULL,
                               0, NULL, NULL);
        
        // KERNEL 1
        clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE,
                            0, ARRAY_SIZE * sizeof(float), antX,
                            0, NULL, NULL);
        clEnqueueReadBuffer(commandQueue, memObjects[3], CL_TRUE,
                            0, ARRAY_SIZE * sizeof(float), antY,
                            0, NULL, NULL);
        clEnqueueReadBuffer(commandQueue, memObjects[8], CL_TRUE,
                            0, ARRAY_SIZE * sizeof(int), lifeStadium,
                            0, NULL, NULL);
        
        
        
        // Write Buffer for Kernel 2
        clEnqueueWriteBuffer(commandQueue, memObjects2[3], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, antX, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[4], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, antY, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[2], CL_FALSE, 0, sizeof(int) * (WIDTH*HEIGHT), pheromonMap, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[0], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, pheromonNewX, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[1], CL_FALSE, 0, sizeof(float) * ARRAY_SIZE, pheromonNewY, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[5], CL_FALSE, 0, sizeof(int) * ARRAY_SIZE, mode, 0, NULL, NULL);
        clEnqueueWriteBuffer(commandQueue, memObjects2[6], CL_FALSE, 0, sizeof(bool) * ARRAY_SIZE, isCarryingFood, 0, NULL, NULL); 
        
        
        
        
        // Execute Kernel 2
        clEnqueueNDRangeKernel(commandQueue, kernel2, 1, NULL,
                               globalWorkSize, NULL,
                               0, NULL, NULL);
        
        
        clEnqueueReadBuffer(commandQueue, memObjects2[5], CL_TRUE,
                            0, ARRAY_SIZE * sizeof(int), mode,
                            0, NULL, NULL);
        
    }
    else {
        art="PU";
        antcl();
    }
    durchschnittsZeit += hey.getElapsedTime().asMilliseconds();
    
    std::cout << art << hey.getElapsedTime().asMilliseconds() << std::endl;
    std::cout << std::endl << "Summe: " << durchschnittsZeit/anzahl;
    anzahl++;
	//antcl();
	clFinish(this->commandQueue);


	return 1;
}

