#include "Physics/dragParticle.hpp"
#include <fstream>

int main () {

	double vel0[3];
	double dt =1e-3;
	vel0[0]=vel0[1]=vel0[2]=1.0;
	double w0[3];
	w0[0]=w0[1]=w0[2]=0.0;
	w0[2]=1;
	Physics::Obliquous ob(Physics::Vector3D(), Physics::Vector3D(vel0), Physics::Vector3D(w0), 6e-3, 4e-4, dt);
	{
	ob.pos = Physics::Vector3D();
	ob.vel = Physics::Vector3D(vel0);
	std::ofstream saida("RK1.dat");

	while(ob.pos.GetElem(2) >= 0) {
		ob.RK1();
		saida << ob.pos << std::endl;
	}
	}
	{
	ob.pos = Physics::Vector3D();
	ob.vel = Physics::Vector3D(vel0);
	std::ofstream saida("RK2.dat");

	while(ob.pos.GetElem(2) >= 0) {
		ob.RK2();
		saida << ob.pos << std::endl;
	}
	}
	{
	ob.pos = Physics::Vector3D();
	ob.vel = Physics::Vector3D(vel0);
	std::ofstream saida("RK4.dat");

	while(ob.pos.GetElem(2) >= 0) {
		ob.RK4();
		saida << ob.pos << std::endl;
	}
	}
	{
	ob.pos = Physics::Vector3D();
	ob.vel = Physics::Vector3D(vel0);
	std::ofstream saida("VelocityVerlet.dat");

	while(ob.pos.GetElem(2) >= 0) {
		ob.VelocityVerlet();
		saida << ob.pos << std::endl;
	}
	}
}
