#include <iostream>
#include <cstdlib>
#include "rules.hpp"
#include "kernels.hpp"
#include "lattice.hpp"
#include "graphicsBase.hpp"

int UniformBetween(int nMax) {return rand()%nMax;}
using namespace std;

int main() {
	bool running = true;
	srand(time(NULL));
	Graphics::GraphicsBase2D graphics(900*sqrt(3.0)/2, 900, 0, 1.0, 0, sqrt(3.0)/2, 0.001, "Gas Lattice CUDA", true);
	Lattice lat(192*4,16);
	//Inicia todos os sites como zero
	for (int i=0; i<lat.N; i++) {
		lat.h_cells1[i]=0;
	}
	//Inicia o quadrado central
	for (int i=lat.L/4; i<3*lat.L/4; i++) {
		for (int j=lat.L/4; j<2*lat.L/4; j++) {
			lat.h_cells1[i*lat.L+j] = FULL; 
			lat.h_cells1[i*lat.L+j] = LEFT; 
		}
		for (int j=2*lat.L/4; j<3*lat.L/4; j++) {
			lat.h_cells1[i*lat.L+j] = FULL;
			lat.h_cells1[i*lat.L+j] = RIGHT; 
		}
	/*	for (int j=lat.L/4; j<3*lat.L/4; j++) {
			if (rand()/(double)RAND_MAX < .2)
				lat.h_cells1[i*lat.L+j] |= BARRIER; 
		}*/

	}

	lat.PrepareToOpenGL();
	lat.CopyToDevice();
	glewInit();
	
	//for(int i=0; i<1e2; i++) {
	while(true){
		graphics.Clear();
		lat.Draw();
		if (glfwGetKey('P') == GLFW_PRESS)
			running=true;
		if (running)
			for (int i=0; i<5;i++)
				lat.FullUpdate();
		graphics.EndFrame();
		cudaThreadSynchronize();
	}
}
