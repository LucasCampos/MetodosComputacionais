/*
 * Class: Drawable class
 * Author: Lucas Costa Campos
 * Date: 06/10/2012
 * 
 * Class representing a drawable object. To be instantiated, 
 * it must overload the Draw method.
 *
 */
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "../Physics/particle.hpp"
#include <GL/glfw.h>
#include <cmath>

namespace Graphics {
	class Drawable{

		private:
			double red;
			double green;
			double blue;

		public: 

			Drawable(): red(1.0), green(0.0), blue(0.0) {};
			Drawable(double _red, double _green, double _blue): red(_red), green(_green), blue(_blue){};

			virtual void Draw() const =0;

			double GetRed() const {return red;}
			double GetBlue() const {return blue;}
			double GetGreen() const {return green;}

			void SetRed(double _red) {red = std::max(_red,0.0);}
			void SetBlue(double _blue) {blue = std::max(_blue,0.0);}
			void SetGreen(double _green) {green = std::max(_green,0.0);}

			void SetColors(double _red, double _green, double _blue) {
				SetRed(_red);
				SetGreen(_green);
				SetBlue(_blue);
			}
			void UseColor() const {
				glColor3d(red, green, blue);
			}
	};
}
#endif
