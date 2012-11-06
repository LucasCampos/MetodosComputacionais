#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <CL/cl.h>

int main() {

	int *A,*B,*C; //Creates pointers of int type. We will use these for host arrays
	cl_mem A_d,B_d,C_d; //Creates pointers of int type. We will use these for device arrays
	int N = 8; //Chooses array size as 8
	int returnValue; //Will be used to recieve return values from OpenCL functions
	int maxSize = 0x100000; //Max size of kernel's source code. 0x100000 corresponds to 1MB

	int buffer_size = sizeof(int)*N; //array size, in bytes.

	//Allocates arrays on host	
	A = new int[N];
	B = new int[N];
	C = new int[N];

	//Starts to creata a OpenCL environment

	//First, we will choose a platform
	cl_platform_id platform; //Will set wich platform we will use
	cl_uint platformsNumber; //Will hold how many platforms are there
	returnValue = clGetPlatformIDs(1, &platform, &platformsNumber); //Fetches 1 platform

	//Now, a device on it
	cl_device_id device; 	//Will set which device we will use
	cl_uint devicesNumber; //Will hold how many devices are there
	returnValue = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &devicesNumber); //Fetches 1 device

	//Initializes a OpenCL Context
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &returnValue);

	//Initializes a command queue
	cl_command_queue commandQueue = clCreateCommandQueue(context, device, 0, &returnValue);

	//Here we end building the OpenCL environment per se.

	//Allocates buffer_size bytes on GPU's global memory for each array
	A_d = clCreateBuffer(context, CL_MEM_READ_ONLY, buffer_size, NULL, &returnValue);
	B_d = clCreateBuffer(context, CL_MEM_READ_ONLY, buffer_size, NULL, &returnValue);
	C_d = clCreateBuffer(context, CL_MEM_WRITE_ONLY, buffer_size, NULL, &returnValue);
	
	for (int i=0; i<N; i++) {//Initialize A and B
		A[i] = N - i;
		B[i] = i;
	}
	
	//Copies A and B to A_d and B_d. We won't copy C because it won't be read.
	returnValue = clEnqueueWriteBuffer(commandQueue, A_d, CL_TRUE, 0, buffer_size, A, 0, NULL, NULL);
	returnValue = clEnqueueWriteBuffer(commandQueue, B_d, CL_TRUE, 0, buffer_size, B, 0, NULL, NULL);

	//Opens kernel source code
	FILE *kernelFile;
    	char *kernelStr;
        size_t kernelSize;
 
    	kernelFile = fopen("kernel.cl", "r");

    	kernelStr = (char*)malloc(maxSize);
    	kernelSize = fread( kernelStr, 1, maxSize, kernelFile);
    	fclose( kernelFile );

	//Creates and compiles the program from source code
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&kernelStr, (const size_t *)&kernelSize, &returnValue);
	returnValue = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	
	//Compile the kernel
	cl_kernel addVec = clCreateKernel(program, "addVec", &returnValue);

	//Set the grid
	size_t TotalSize = 8;
	size_t ThreadsPerBlock = 8;

	//Set kernel arguments
	returnValue = clSetKernelArg(addVec, 0, sizeof(cl_mem), (void *)&A_d);
    	returnValue = clSetKernelArg(addVec, 1, sizeof(cl_mem), (void *)&B_d);
    	returnValue = clSetKernelArg(addVec, 2, sizeof(cl_mem), (void *)&C_d);

	returnValue = clEnqueueNDRangeKernel(commandQueue, addVec, 1, NULL, &TotalSize, &ThreadsPerBlock, 0, NULL, NULL); //Launch the kernel.

	returnValue = clEnqueueReadBuffer(commandQueue, C_d, CL_TRUE, 0, buffer_size, C, 0, NULL, NULL); //Copies from C_d to C.

	//Forces commmand queue to finish;
	returnValue = clFlush(commandQueue);
	returnValue = clFinish(commandQueue);	

	for (int i=0; i<N; i++) { //Checks if all the operations were done right
		std::cout << A[i] << " + " << B[i] << " = " << C[i] << std::endl;
	}
	
	//Clean arrays on host
	free(A);
	free(B);
	free(C);

	//Clean arrays on device
	returnValue = clReleaseKernel(addVec);
	returnValue = clReleaseProgram(program);
	returnValue = clReleaseMemObject(A_d);
	returnValue = clReleaseMemObject(B_d);
	returnValue = clReleaseMemObject(C_d);
	returnValue = clReleaseCommandQueue(commandQueue);
	returnValue = clReleaseContext(context);

	return 0;
}
