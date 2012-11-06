#include <iostream>
#include <fstream>
#include "Physics/pendulum.hpp"

using namespace Physics;

double VelocityFromEnergy(double Ec) {
	        return sqrt(2.0*Ec);
}

int main() {

	double v0[1];
	v0[0] = VelocityFromEnergy(1);
	double g[2];
	g[0] =0;
	g[1] =-1;
	double dt = 0.001;
	Pendulum pendulum (Vector<1,double>(), Vector<1,double>(v0), Vector<2,double> (), Vector<2,double>(g), 1.0, dt);

	std::ofstream sP("simpleP.dat");
	std::ofstream sPV("simplePV.dat");

	for (double t=0; t<60; t+=dt) {
		pendulum.RK2();
		pendulum.ContourConditions();
		sP << pendulum.PosInWorldCoordinates() << std::endl;
		sPV << pendulum.pos << "   " << pendulum.vel << std::endl;
	}
}

		
