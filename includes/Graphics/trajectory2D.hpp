/*
 * Class: Drawable class
 * Author: Lucas Costa Campos
 * Date: 08/10/2012
 * 
 * Class to draw trajectories. It implements the Draw
 * method inheritated from Drawable
 *
 */
#ifndef TRAJECTORY2D_HPP
#define TRAJECTORY2D_HPP
#include "drawable.hpp"
#include <vector>
#include <GL/glfw.h>
#include <cmath>

namespace Graphics {
	class Trajectory2D: public Drawable{

		private:

			std::vector<Physics::Vector<2,double> > points;

		public: 

			Trajectory2D(): Drawable() {};
			Trajectory2D(double _red, double _green, double _blue): Drawable(_red, _green, _blue){};
			void AddPoint(const Physics::Vector<2,double>& newP) {points.push_back(newP);}
			virtual void Draw() const{
				UseColor();
				glBegin(GL_LINE_STRIP);
				for (int i=0; i<points.size(); i++) {
					glVertex2d(points[i].GetElem(0), points[i].GetElem(1));
				}
				glEnd();
			};
	};
}
#endif
