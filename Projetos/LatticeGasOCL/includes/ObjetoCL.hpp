#ifndef CLOBJECT_HPP
#define CLOBJECT_HPP
#include <CL/cl.h>

class CLObject {

public:

	cl_platform_id usedPlatform;
	cl_device_id usedId;
	cl_cl_

	void InitiateOpenCL(int platNum=0, int devNum=0, cl_device_type type=CL_DEVICE_TYPE_ALL) {
		cl_platform_id platform[50]; //Will set wich platform we will use
		cl_uint platformsNumber; //Will hold how many platforms are there
		returnValue = clGetPlatformIDs(50, platform, &platformsNumber); //Fetches up to fifty platforms
		cl_device_id device[10]; 	//Will set which device we will use
		cl_uint devicesNumber; //Will hold how many devices are there
		clGetDeviceIDs(platform[platNum], type, 10, device, &devicesNumber); //Fetches up to ten devices
		char name[2048];
		clGetDeviceInfo(device[devNum], CL_DEVICE_NAME, 2048*sizeof(char), name, NULL); //Get the device name
		clGetDeviceInfo(device[devNum], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &cores, NULL);
		std::cout << name << " with " << cores << " cores. It is a";

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
}


#endif
