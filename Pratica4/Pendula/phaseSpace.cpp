#include <iostream>
#include <fstream>
#include "../../includes/Physics/pendulum.hpp"
#include <cstdlib>

using namespace Physics;

double VelocityFromEnergy(double Ec) {
	        return sqrt(2.0*Ec);
}

int main() {

	double v0[1];
	double p0[1];
		p0[0]= 0.0;
	double g[2];
		g[0] =0;
		g[1] =-1;
	double dt = 0.001;
	int N=25;
	int counter = 0;
	const int nCount =50;

	std::vector<Physics::Pendulum> pendula(N);
	{
		int i=0;
		for (double kinEnergy = .5; kinEnergy < 2.5; kinEnergy += 0.4){
			v0[0] = VelocityFromEnergy(kinEnergy);
			for (p0[0] = 0; p0[0] < .9; p0[0] += 0.2){

				pendula[i] = Pendulum(Vector<1,double>(p0), Vector<1,double>(v0), Vector<2,double> (), Vector<2,double>(g), 1.0, dt);

				i++;
			}
		}
	}

	std::ofstream sP("pos.dat");
	std::ofstream sPV("PV.dat");

	for (double t=0; t<30; t+=dt) {
		for (int i=0; i<pendula.size(); i++) {
			pendula[i].RK2();
			pendula[i].ContourConditions();
			if (counter %nCount == 0) {
				sP << pendula[i].PosInWorldCoordinates() << std::endl;
				sPV << pendula[i].pos << "   " << pendula[i].vel << std::endl;
			}
		}
		if (counter %nCount == 0) {
			sP << std::endl;
			sPV <<std::endl;
		}
		counter++;
	}
}


