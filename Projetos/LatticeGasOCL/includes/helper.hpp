#ifndef HELPER_HPP
#define HELPER_HPP
#include <GL/glew.h>
#include <GL/glfw.h>
#include <cuda_gl_interop.h>
#include <cstdio>

#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))
inline int ConvertSMVer2Cores(int major, int minor)
{
	// Defines for GPU Architecture types (using the SM version to determine the # of cores per SM
	typedef struct
	{
		int SM; // 0xMm (hexidecimal notation), M = SM Major version, and m = SM minor version
		int Cores;
	} sSMtoCores;

	sSMtoCores nGpuArchCoresPerSM[] =
	{
		{ 0x10,  8 },
		{ 0x11,  8 },
		{ 0x12,  8 },
		{ 0x13,  8 },
		{ 0x20, 32 },
		{ 0x21, 48 },
		{   -1, -1 }
	};

	int index = 0;
	while (nGpuArchCoresPerSM[index].SM != -1)
	{
		if (nGpuArchCoresPerSM[index].SM == ((major << 4) + minor) )
		{
			return nGpuArchCoresPerSM[index].Cores;
		}
		index++;
	}
	std::cout << "MapSMtoCores undefined SMversion" <<  major << "." << minor <<std::endl;
	return -1;
}

static void HandleError( cudaError_t err, const char *file, int line ) {
	if (err != cudaSuccess) {
		printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
				file, line );
		exit( EXIT_FAILURE );
	}
}

GLuint createVBO(const void* data, int dataSize, GLenum target, GLenum usage) {
	GLuint id = 0;  // 0 is reserved, glGenBuffersARB() will return non-zero id if success

	glGenBuffersARB(1, &id);                        // create a vbo
	glBindBufferARB(target, id);                    // activate vbo id to use
	glBufferDataARB(target, dataSize, data, usage); // upload data to video card

	// check data size in VBO is same as input array, if not return 0 and delete VBO
	int bufferSize = 0;
	glGetBufferParameterivARB(target, GL_BUFFER_SIZE_ARB, &bufferSize);
	if(dataSize != bufferSize)
	{
		glDeleteBuffersARB(1, &id);
		id = 0;
		std::cout << "[createVBO()] Data size is mismatch with input array\n";
	}

	return id;      // return VBO id
}

#endif
