#include "Physics/dragParticle.hpp"
#include <fstream>

int main () {

	double vel0[3];
	double dt =1e-3;
	vel0[0]=vel0[1]=vel0[2]=0.0;
	vel0[1]=10;
	double w0[3];
	w0[0]=w0[1]=w0[2]=0.0;
	w0[2]=1;
	Physics::Drag<3,double> mag(Physics::Vector3D(), Physics::Vector3D(vel0), Physics::Vector3D(w0), .1, 1, dt);
	{

		std::ofstream saida("RK1.dat");
		for (double t=0; t<100; t+=dt){
			mag.RK1();
			std::cout << t << std::endl;
			saida << mag.pos << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D();
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK2.dat");
		for (double t=0; t<100; t+=dt){
			mag.RK2();
			std::cout << t << std::endl;
			saida << mag.pos << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D();
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK4.dat");
		for (double t=0; t<100; t+=dt){
			mag.RK4();
			std::cout << t << std::endl;
			saida << mag.pos << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D();
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("VelocityVerlet.dat");
		for (double t=0; t<100; t+=dt){
			mag.VelocityVerlet();
			std::cout << t << std::endl;
			saida << mag.pos << std::endl;
		}
	}
}
