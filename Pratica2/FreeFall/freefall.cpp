#include "Physics/dragParticle.hpp"
#include <fstream>

int main () {

	double dt =1e-3;
	double pos0[3];
	pos0[0]=pos0[1]=pos0[2]=0;
	pos0[2] = 150;
	double vel0[3];
	vel0[0]=vel0[1]=vel0[2]=0;
	double w0[3];
	w0[0]=w0[1]=w0[2]=0.0;
	Physics::Obliquous ob(Physics::Vector3D(pos0), Physics::Vector3D(vel0), Physics::Vector3D(w0), 0, 0, dt);
	{
		ob.pos = Physics::Vector3D(pos0);
		ob.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK1.dat");
		std::ofstream saidaV("RK1_Vel.dat");

		while(ob.pos.GetElem(2) >= 0) {
			ob.RK1();
			saida << ob.pos << std::endl;
			saidaV << ob.vel << std::endl;
		}
	}
	{
		ob.pos = Physics::Vector3D(pos0);
		ob.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK2.dat");
		std::ofstream saidaV("RK2_Vel.dat");

		while(ob.pos.GetElem(2) >= 0) {
			ob.RK2();
			saida << ob.pos << std::endl;
			saidaV << ob.vel << std::endl;
		}
	}
	{
		ob.pos = Physics::Vector3D(pos0);
		ob.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK4.dat");
		std::ofstream saidaV("RK4_Vel.dat");

		while(ob.pos.GetElem(2) >= 0) {
			ob.RK4();
			saida << ob.pos << std::endl;
			saidaV << ob.vel << std::endl;
		}
	}
	{
		ob.pos = Physics::Vector3D(pos0);
		ob.vel = Physics::Vector3D(vel0);
		std::ofstream saida("VelocityVerlet.dat");
		std::ofstream saidaV("VelocityVerlet_Vel.dat");

		while(ob.pos.GetElem(2) >= 0) {
			ob.VelocityVerlet();
			saida << ob.pos << std::endl;
			saidaV << ob.vel << std::endl;
		}
	}
}
