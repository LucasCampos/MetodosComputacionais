#include <iostream>
#include <fstream>
#include "Physics/spring.hpp"

int main() {

	double v0[3];
	v0[0]= v0[1] = v0[2] = 0.0;
	v0[0] = 1;
	double dt = 0.001;
	Physics::Spring <1,double> spring( Physics::Vector<1,double>(), Physics::Vector<1,double>(v0), Physics::Vector<1,double>(),0,1.0,dt);

	std::ofstream sP("simpleP.dat");
	std::ofstream sPV("simplePV.dat");

	for (double t=0; t<60; t+=dt) {
		spring.VelocityVerlet();
		sP << spring.pos << std::endl;
		sPV << spring.pos << "   " << spring.vel << std::endl;
	}
}

		
