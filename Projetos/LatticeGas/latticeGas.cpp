#include "lattice.hpp"
#include "graphicsBase.hpp"
#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

int UniformBetween(int nMax) {return rand()%nMax;}
using namespace std;

int main() {
	bool running = true;
	srand(time(NULL));
	SetRules();
	Lattice lat(192*2);
	Graphics::GraphicsBase2D graphics(800*sqrt(3.0)/2, 800, 0, 1.0, 0, sqrt(3.0)/2, 0.001, "Gas Lattice", true);
	for (int i=0; i<lat.N; i++) {
		lat.cells1[i].current=0;
	}

	//Inicia o quadrado central
	for (int i=lat.L/4; i<3*lat.L/4; i++) {
		for (int j=lat.L/4+1; j<3*lat.L/4+1; j++) {
			lat.cells1[i*lat.L+j].current = (~0) ^ (STATIONARY | BARRIER); 
		}
	}
	while(true){
		graphics.Clear();
		if (glfwGetKey('P') == GLFW_PRESS)
			running=true;
		if (running)
			for (int j=0; j<5; j++) {
				lat.FullUpdate();
			}
		lat.Draw();
		graphics.EndFrame();
	}
}
