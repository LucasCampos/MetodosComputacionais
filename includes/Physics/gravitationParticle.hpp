/*
 * Class: Particle with gravitational forces
 * Author: Lucas Costa Campos
 * Date: 06/10/2012
 * 
 * A n-dimensional particle with Newton's gravitation,
 * i.e., F=M/r^2
 * 
 */

#ifndef GRAVITATION_PARTICLE_HPP
#define GRAVITATION_PARTICLE_HPP
#include "particle.hpp"
#include <vector>
#include "../Graphics/drawable.hpp"

namespace Physics{

	template <unsigned int N, class T>
		class Gravitation: public Particle<N,T> {

			private:
				std::vector<Gravitation*> others;

			public:
				T mass;
				Gravitation(): Particle<N,T>(), mass(1.0) {};
				Gravitation(Vector<N,T> _pos, Vector<N,T> _vel, T _mass): Particle<N,T>(_pos, _vel), mass(_mass) {};
				Gravitation(Vector<N,T> _pos, Vector<N,T> _vel, double _dt, T _mass): Particle<N,T>(_pos, _vel,_dt), mass(_mass){
				};

				void SetOthers(const std::vector<Gravitation*>& o) {
					others =o;
				}

				virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, T t) const {
					Vector<N,T> force;
					for (int i=0; i<others.size(); i++){
						if (this != others[i]) {
							Vector<N,T> dist = p - others[i]->pos;
							force -= dist*(others[i]->mass/(dist.MagnitudeSquared()*dist.Magnitude()));
						}
					}
					return force;
				};

		};

	class DrawableGravitation: public Gravitation<2,double>, public Graphics::Drawable {

				private:
					double radius;
				public:

				DrawableGravitation(): Gravitation<2,double>(), Drawable() {};
				DrawableGravitation(Vector<2,double> _pos, Vector<2,double> _vel, double _mass): Gravitation<2,double>(_pos, _vel, _mass),Drawable() {};
				DrawableGravitation(Vector<2,double> _pos, Vector<2,double> _vel, double _dt, double _mass): Gravitation<2,double>(_pos, _vel,_dt, _mass), Drawable(), radius(1.0){};
				DrawableGravitation(Vector<2,double> _pos, Vector<2,double> _vel, double _dt, double _mass, double _radius): Gravitation<2,double>(_pos, _vel,_dt, _mass), Drawable(), radius(_radius){};
				DrawableGravitation(Vector<2,double> _pos, Vector<2,double> _vel, double _dt, double _mass, double _radius, double _red, double _green, double _blue): Gravitation<2,double>(_pos, _vel,_dt, _mass), Drawable(_red, _green, _blue), radius(_radius) {};

				virtual void Draw() const {
					double angulo,X,Y;
	
					UseColor();
					glBegin(GL_TRIANGLE_FAN);
					glVertex2d(Particle<2,double>::pos.GetElem(0), Particle<2,double>::pos.GetElem(1));
					for (int i=0; i<=36; i++) {
						angulo = i/5.729577957795135;
						X=pos.GetElem(0)+ radius*sin(angulo);
						Y=pos.GetElem(1)+ radius*cos(angulo);
						glVertex2d(X,Y);
					}   
					glEnd();
				}


	};
}

#endif
