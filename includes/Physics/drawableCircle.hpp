/*
 * Class: 2-Dimensional Drawable Circle
 * Author: Lucas Costa Campos
 * Date: 06/10/2012
 * 
 * Template representing a particle circle that can be drawn.
 * The draw method from Drawable was overloaded, but not accel.
 *
 * It uses 36 triangles to draw the circle.
 *
 *
 */
#ifndef DRAWABLE_CIRCLE_HPP
#define DRAWABLE_CIRCLE_HPP
#include "drawableParticle.hpp"

namespace Physics {
		class DrawableCircle: public DrawableParticle<2,double> {

			private: 
				double radius;
			public:
				DrawableCircle(): DrawableParticle<2,double>(), radius(1.0){};
				DrawableCircle(Vector<2,double> _pos, Vector<2,double> _vel): DrawableParticle<2,double>(_pos, _vel), radius(1.0){};
				DrawableCircle(Vector<2,double> _pos, Vector<2,double> _vel, double _dt): DrawableParticle<2,double>(_pos, _vel, _dt), radius(1.0){};
				DrawableCircle(Vector<2,double> _pos, Vector<2,double> _vel, double _dt, double _radius): DrawableParticle<2,double>(_pos, _vel, _dt), radius(_radius){};
				DrawableCircle(Vector<2,double> _pos, Vector<2,double> _vel, double _dt, double _red, double _blue, double _green, double _radius): DrawableParticle<2,double>(_pos, _vel, _dt, _red, _green, _blue), radius(_radius){};

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
