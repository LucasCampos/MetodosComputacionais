/*
 * Class: Particle with Yukawa forces 
 * Author: Lucas Costa Campos
 * Date: 20/10/2012
 * 
 * 
 */
#include "particle.hpp"
#ifndef YUKAWA_PARTICLE_HPP
#define YUKAWA_PARTICLE_HPP
#include "../Graphics/drawable.hpp"

namespace Physics{

	template <unsigned int N, class T>
		class Yukawa: public Particle<N,T> {


			public:
				Yukawa(): Particle<N,T>() {};
				Yukawa(Vector<N,T> _pos, Vector<N,T> _vel): Particle<N,T>(_pos, _vel) {};
				Yukawa(Vector<N,T> _pos, Vector<N,T> _vel, double _dt): Particle<N,T>(_pos, _vel,_dt){ };
				virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, T t) const {
					T r2 = p.MagnitudeSquared();
					T r = sqrt(r2);
					return p*(exp(-r)*(r+1)/(r2*r));
				}
		};

	class DrawableYukawa: public Yukawa<3,double>, public::Graphics::Drawable {
		public:

			DrawableYukawa(): Yukawa<3,double>(), Drawable() {};
			DrawableYukawa(Vector<3,double> _pos, Vector<3,double> _vel): Yukawa<3,double>(_pos, _vel),Drawable() {};
			DrawableYukawa(Vector<3,double> _pos, Vector<3,double> _vel, double _dt): Yukawa<3,double>(_pos, _vel,_dt), Drawable(){};
			DrawableYukawa(Vector<3,double> _pos, Vector<3,double> _vel, double _dt, double _red, double _green, double _blue): Yukawa<3,double>(_pos, _vel,_dt), Drawable(_red, _green, _blue) {};
/*
			virtual void Draw() const {
				double angulo,X,Y;

				UseColor();
				glBegin(GL_POINT);
					glVertex3d(Particle<3,double>::pos.GetElem(0),Particle<3,double>::pos.GetElem(1), Particle<3,double>::pos.GetElem(2));
				glEnd();
			}
*/
			virtual void Draw() const {
				double angulo,X,Y;
				double radius= 0.1;
				UseColor();
				glBegin(GL_TRIANGLE_FAN);
				glVertex2d(Particle<3,double>::pos.GetElem(0), Particle<3,double>::pos.GetElem(1));
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
