#include "lattice.hpp"
#include <iostream>
#include <cstdlib>
int UniformBetween(int nMax) {return rand()%nMax;}
	using namespace std;

int main() {
	SetRules();
	Lattice lat(192*2);
	//Inicia todos os sites como zero
	for (int i=0; i<lat.N; i++) {
		lat.cells1[i].current = (~0) ^ (STATIONARY | BARRIER); 
	}

	for (int i=0; i<5e4; i++){
			lat.FullUpdate();
	}
}
