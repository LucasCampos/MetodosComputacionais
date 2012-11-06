#include <iostream>
#include <fstream>
#include "../includes/Graphics/graphicsBase.hpp"
#include "../includes/Graphics/drawable.hpp"
#include "../includes/Physics/yukawaParticle.hpp"

using Physics::Vector;
using namespace std;

double Uniforme() {return rand()/((double)RAND_MAX);}
double UniformeC() {return 2.0*(Uniforme()-0.5);}

void MakeBin(const std::vector<Physics::DrawableYukawa*>& yukawa, const std::vector<double>& b, int nBinsB, int nBinsAngle) {

	const double maxB=3.0;
	const double deltaB=maxB/nBinsB;
	
	const double maxTheta=M_PI;
	const double deltaTheta=maxTheta/nBinsAngle;

	std::vector<double> theta(yukawa.size());
	for (int i=0; i<yukawa.size(); i++) {
		Vector<3,double> p = yukawa[i]->pos;
		p.Normalize();
		theta[i] = abs(acos(p.GetElem(0)));//angle with x axis
	}

	int distribuicao[nBinsB+1][nBinsAngle+1];
	for(int i=0; i<=nBinsB; i++){
		for(int j=0; j<=nBinsAngle; j++) {
			distribuicao[i][j]=0;
		}
	}


	for (int i=0; i<theta.size(); i++) {
		int locTheta=theta[i]/deltaTheta;
		int locB=b[i]/deltaB;
		distribuicao[locB][locTheta]++;
		//cout << locB*deltaB << "   " << locTheta*deltaTheta << endl;
	}
	
	ofstream saida("Hist3D.dat");
	for(int i=0; i<=nBinsB; i++){
		for(int j=0; j<=nBinsAngle; j++) {
			saida << i*deltaB << "  " << j*deltaTheta << "  " << distribuicao[i][j] << endl;
		}
	}

}

int main() {
	double dt =0.01;
	int stepsBetweenFrames = 50;
	const double tmax=5e1;
	const int nPassos = tmax/dt;
	double t=0;

	//Graphics::GraphicsBase2D graphic(800,800,-20.0, 20.0, -20.0, 20.0, 0.0, "Gravitation", true);

	std::vector<Physics::DrawableYukawa*> yukawaOriginal(4000);
	std::vector<double> b(yukawaOriginal.size());

	for (int i=0; i<yukawaOriginal.size(); i++) {
		double vel[3];
		vel[0]=vel[1]=vel[2] = 0;
		vel[0]=1;
		double pos[3];
		double teta = Uniforme()*2*M_PI;
		double r = Uniforme()*3;
		pos[0]=-4;
		pos[1]=r*sin(teta);
		pos[2]=r*cos(teta);

		yukawaOriginal[i] = new Physics::DrawableYukawa(pos,vel,dt);
		b[i] = sqrt(pos[1]*pos[1]+pos[2]*pos[2]);
	}

	for(int passos=0; passos<nPassos; passos++) {
		for (int i=0; i<yukawaOriginal.size(); i++){
			yukawaOriginal[i]->RK4();
		}
	}
	MakeBin(yukawaOriginal, b, 30, 30) ;
}
