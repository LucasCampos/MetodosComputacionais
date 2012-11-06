/* Simple program to list all openCL device on a computer
 * Feel free to share and enjoy this program.
 * Lucas Campos - UFPE
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <CL/cl.h>

int main() {

	int returnValue; //Will be used to recieve return values from OpenCL functions
	//Starts to creata a OpenCL environment

	//First, we will choose a platform
	cl_platform_id platform[50]; //Will set wich platform we will use
	cl_uint platformsNumber; //Will hold how many platforms are there
	returnValue = clGetPlatformIDs(50, platform, &platformsNumber); //Fetches up to fifty platforms
	std::cout << "There are " << platformsNumber << " platforms." << std::endl;

	for (int i=0; i<platformsNumber; i++) {
		char name[2048];
		//Now, a device on it
		clGetPlatformInfo(platform[i],CL_PLATFORM_NAME, 2048*sizeof(char), name,NULL); //Gets the platform name
		cl_device_id device[10]; 	//Will set which device we will use
		cl_uint devicesNumber; //Will hold how many devices are there
		clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_ALL, 10, device, &devicesNumber); //Fetches up to ten devices
		std::cout << i+1 << ": " << name << " with " << devicesNumber << " devices. " << std::endl;
		
		for (int j=0; j<devicesNumber; j++){
			cl_uint cores; //Will hold how many cores are on this device
			clGetDeviceInfo(device[j], CL_DEVICE_NAME, 2048*sizeof(char), name, NULL); //Get the device name
			clGetDeviceInfo(device[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &cores, NULL);
			std::cout << i+1 << "." << j+1 << ": " << name << " with " << cores << " cores. It is a";

			cl_device_type type;

			
			clGetDeviceInfo(device[j], CL_DEVICE_TYPE, sizeof(cl_device_type), &type, NULL); //Discover what's the type of the device
			switch (type) {
				case CL_DEVICE_TYPE_CPU:
					std::cout << " CPU." << std::endl;
					break;
				case CL_DEVICE_TYPE_GPU:
					std::cout << " GPU." << std::endl;
					break;
				case CL_DEVICE_TYPE_ACCELERATOR:
					std::cout << " Accelerator." << std::endl;
					break;
			}
		


		}
		std::cout << std::endl;
	}

	return 0;
}
