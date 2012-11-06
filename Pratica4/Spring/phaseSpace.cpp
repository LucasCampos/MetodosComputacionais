#include <iostream>
#include <fstream>
#include "../../includes/Physics/spring.hpp"
#include <cstdlib>

int main() {

	double v0[3];
	v0[0]= v0[1] = v0[2] = 0.0;
	double p0[3];
	p0[0]= p0[1] = p0[2] = 0.0;
	double dt = 0.001;
	int N=25;
	int counter = 0;
	const int nCount =50;

	std::vector<Physics::Spring <1,double> > springs(N);
	{
		int i=0;
		for (v0[0] = 1; v0[0] < 1.9; v0[0] += 0.2){
			for (p0[0] = 1; p0[0] < 1.9; p0[0] += 0.2){

				springs[i] = Physics::Spring<1,double>( Physics::Vector<1,double>(p0), Physics::Vector<1,double>(v0), Physics::Vector<1,double>(),0,1.0,dt);
				i++;
			}
		}
	}

	std::ofstream sP("pos.dat");
	std::ofstream sPV("PV.dat");

	for (double t=0; t<30; t+=dt) {
		for (int i=0; i<springs.size(); i++) {
			springs[i].RK4();
			if (counter %nCount == 0) {
				sP << springs[i].pos << std::endl;
				sPV << springs[i].pos << "   " << springs[i].vel << std::endl;
			}
		}
		if (counter %nCount == 0) {
			sP << std::endl;
			sPV <<std::endl;
		}
		counter++;
	}
}


