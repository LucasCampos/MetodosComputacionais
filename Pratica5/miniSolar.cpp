#include <iostream>
#include "../includes/Graphics/graphicsBase.hpp"
#include "../includes/Graphics/drawable.hpp"
#include "../includes/Graphics/trajectory2D.hpp"
#include "../includes/Physics/gravitationParticle.hpp"

using Physics::Vector;

int main() {
	double dt =0.001;
	int stepsBetweenFrames = 100;

	Graphics::GraphicsBase2D graphic(800,800,-5.0, 5.0, -5.0, 5.0, 0.0, "Gravitation", true);

	std::vector<Physics::DrawableGravitation*> planetsOriginal(3);
	std::vector<Physics::Gravitation<2,double>*> planetsGrav(planetsOriginal.size());
	std::vector<Graphics::Trajectory2D*> planetsTraj(planetsOriginal.size());

	{
		double mass = 1.0;
		double pos[2] = {0.0,0.0};
		double vel[2] = {0.0,0.0};
		double radius = sqrt(mass/M_PI);

		planetsOriginal[0] = new Physics::DrawableGravitation(Vector<2,double>(pos), Vector<2,double>(vel), dt, mass,radius, 1.0, 1.00, .0);
		planetsTraj[0] = new Graphics::Trajectory2D(1.0,1.0,0.0);
	}
	{
		double mass = 0.1;
		double pos[2] = {1.0,0.0};
		double vel[2] = {0.0,1.0};
		double radius = sqrt(mass/M_PI);

		planetsOriginal[1] = new Physics::DrawableGravitation(Vector<2,double>(pos), Vector<2,double>(vel), dt, mass, radius);
		planetsTraj[1] = new Graphics::Trajectory2D(1.0,0.0,0.0);
	}
	{
		double mass = 0.2;
		double pos[2] = {-3.0,0.0};
		double vel[2] = {0.0,sqrt(1.0/3)};
		double radius = sqrt(mass/M_PI);

		planetsOriginal[2] = new Physics::DrawableGravitation(Vector<2,double>(pos), Vector<2,double>(vel), dt, mass,radius, 0.0,0.0,1.0);
		planetsTraj[2] = new Graphics::Trajectory2D(0.0,0.0,1.0);
	}

	for (int i=0; i<planetsOriginal.size(); i++){
		planetsGrav[i] = planetsOriginal[i];
	}

	for (int i=0; i<planetsOriginal.size(); i++){
		planetsOriginal[i]->SetOthers(planetsGrav);
	}

	while(true){
		for (int steps=0; steps<stepsBetweenFrames; steps++)
			for (int i=1; i<planetsGrav.size(); i++){
				planetsGrav[i]->RK4();
			}
		for (int i=0; i<planetsTraj.size(); i++)
			planetsTraj[i]->AddPoint(planetsGrav[i] -> pos);

		graphic.Clear();
		graphic.Draw(planetsTraj);
		graphic.Draw(planetsOriginal);
		graphic.EndFrame();
	}
}
