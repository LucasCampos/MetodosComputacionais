#ifndef CELL_HPP
#define CELL_HPP
#include <GL/glew.h>
#include <cstdio>

/*
 * Indexes:
 * RIGHT 0
 * RIGHT_DOWN 1
 * LEFT_DOWN 2
 * LEFT 3
 * LEFT_UP 4
 * RIGHT_UP 5
 */

__device__ __host__ inline int DealWithBoundaries(int a, int N) {
	if (a < 0) return a+N;
	//if (a == N) return 0;
	return a%N;
}

__device__ __host__ inline int RightNeigh    (int i, int L, int N) { return DealWithBoundaries((i+1),N);}
__device__ __host__ inline int RightDownNeigh(int i, int L, int N) { return DealWithBoundaries((i+L),N);}
__device__ __host__ inline int LeftDownNeigh (int i, int L, int N) { return DealWithBoundaries((i+L-1),N);}
__device__ __host__ inline int LeftNeigh     (int i, int L, int N) { return DealWithBoundaries((i-1),N);}
__device__ __host__ inline int LeftUpNeigh   (int i, int L, int N) { return DealWithBoundaries((i-L),N);}
__device__ __host__ inline int RightUpNeigh  (int i, int L, int N) { return DealWithBoundaries((i-L+1),N);}

__global__ void UpdateCells(int* inCells, int* outCells, int* rules, int L, int N) {
	const int i=blockIdx.x*blockDim.x+threadIdx.x;
	if (i >= N) {
		return;
	}
	int newCurr = inCells[i] & (BARRIER|STATIONARY);
	newCurr |= inCells[RightNeigh(i,L,N)]     & RIGHT;
	newCurr |= inCells[RightDownNeigh(i,L,N)] & RIGHT_DOWN;
	newCurr |= inCells[LeftDownNeigh(i,L,N)]  & LEFT_DOWN;
	newCurr |= inCells[LeftNeigh(i,L,N)]      & LEFT;
	newCurr |= inCells[LeftUpNeigh(i,L,N)]    & LEFT_UP;
	newCurr |= inCells[RightUpNeigh(i,L,N)]   & RIGHT_UP;
	//if (i%L ==0 ) newCurr=0;
	//if (i<L) newCurr=0;
	
	outCells[i] = rules[newCurr];
	
}

__device__ __host__ int CountMass(int cell) {
	int mass=0;
	int curr = cell;
	while (curr > 0) {
		mass += curr&1;
		curr = curr >> 1;
	}
	return mass;
}

__global__ void GetCellsMass(int* cells, int* cellMass, int N) {
	const int i=blockIdx.x*blockDim.x+threadIdx.x;
	cellMass[i] = CountMass(cells[i]);
}



__global__ void Density(int* cells, GLfloat* color, int N) {
	const int i=blockIdx.x*blockDim.x+threadIdx.x;
	if (i >= N) {
		return;
	}
	const int iC=i*12;
	int curr = cells[i];
	if((curr & BARRIER) != 0)  {
		for (int j=0; j<12; j+=3) {
			color[iC+j] = 0;
			color[iC+j+1] = 0;
			color[iC+j+2] = .3;
		}
		return;
	}
	float den=CountMass(curr);

	den/=8;

	for (int j=0; j<12; j+=3) {
		color[iC+j] = den;
		color[iC+j+1] = 0;
		color[iC+j+2] = 0;
	}
}

#endif
