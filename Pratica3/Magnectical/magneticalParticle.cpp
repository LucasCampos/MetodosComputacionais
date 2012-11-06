#include "Physics/magnetParticle.hpp"
#include <fstream>

int main () {

	double dt =1e-3;
	double t =0;

	double pos0[3];
	pos0[0]=pos0[1]=pos0[2]=0;
	pos0[0] = -2;
	
	double vel0[3];
	vel0[0]=vel0[1]=vel0[2]=0;
	vel0[0] = 2.0;

	double B[3];
	B[0]= B[1]= B[2]=0.0;
	B[2]= 1.0;
	
	double E[3];
	E[0]= E[1]= E[2]=0.0;
	E[1]= 1.0;

	Physics::Magnet<3,double> mag(Physics::Vector3D(pos0), Physics::Vector3D(vel0), Physics::Vector3D(E), Physics::Vector3D(B), 1.0, dt);
	{
		mag.pos = Physics::Vector3D(pos0);
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK1.dat");
		std::ofstream saidaV("RK1_Vel.dat");

		for (t =0; t< 50; t+= dt) {
			mag.RK1();
			saida << mag.pos << std::endl;
			saidaV << mag.vel << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D(pos0);
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK2.dat");
		std::ofstream saidaV("RK2_Vel.dat");

		for (t =0; t< 50; t+= dt) {
			mag.RK2();
			saida << mag.pos << std::endl;
			saidaV << mag.vel << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D(pos0);
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("RK4.dat");
		std::ofstream saidaV("RK4_Vel.dat");

		for (t =0; t< 50; t+= dt) {
			mag.RK4();
			saida << mag.pos << std::endl;
			saidaV << t << "  " << mag.vel << std::endl;
		}
	}
	{
		mag.pos = Physics::Vector3D(pos0);
		mag.vel = Physics::Vector3D(vel0);
		std::ofstream saida("VelocityVerlet.dat");
		std::ofstream saidaV("VelocityVerlet_Vel.dat");

		for (t =0; t< 50; t+= dt) {
			mag.VelocityVerlet();
			saida << mag.pos << std::endl;
			saidaV << t << "  " << mag.vel << std::endl;
		}
	}
}
