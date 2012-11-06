/*
 * Class: Pendulum
 * Author: Lucas Costa Campos
 * Date: 29/09/2012
 * 
 * ND pendulum
 * 
 * Please do notice that pos and vel are *angular* values
 *
 */
#ifndef PENDULUM_PARTICLE_HPP
#define PENDULUM_PARTICLE_HPP
#include "particle.hpp"

namespace Physics{

	class Pendulum: public Particle<1,double> {

		private:
			//Position of equilibrium
			Vector<2,double> p0;
			//Length
			double l;
			//Gravity
			Vector<2,double> g;

		public:
			Pendulum(): Particle<1,double>(), l(1) {g.SetElem(1,-9.8);};
			Pendulum(Vector<1,double> _pos, Vector<1,double> _vel): Particle<1,double>(_pos, _vel), l(1.0){g.SetElem(1,-9.8);};
			Pendulum(Vector<1,double> _pos, Vector<1,double> _vel, Vector<2,double> _p0, Vector<2,double> _g, double _l, double _dt): Particle<1,double>(_pos, _vel,_dt), p0(_p0), g(_g), l(_l){
			};
			virtual Vector<1,double> Accel(const Vector<1,double>& p, const Vector<1,double>& v, double t) const {

				Vector<2,double> currP = RectangularCoordinates(p)*l;
				double newComp[1];
				newComp[0]= currP.GetElem(0)*g.GetElem(1) - currP.GetElem(1)*g.GetElem(0);
				return Vector<1,double>(newComp);

			} 

			void ContourConditions() {
				if (pos.GetElem(0) > M_PI)
					pos.SetElem(0,pos.GetElem(0)-2*M_PI);
				if (pos.GetElem(0) < -M_PI)
					pos.SetElem(0,pos.GetElem(0)+2*M_PI);
			}

			Vector<2,double> PosInWorldCoordinates() const  {
				return RectangularCoordinates(pos)*l + p0;
			}

			Vector<2,double> RectangularCoordinates(const Vector<1,double>& v) const  {
				double comp[2];
				comp[0] = sin(v.GetElem(0));
				comp[1] = -cos(v.GetElem(0));
				return Vector<2,double> (comp);
			}
	};

}

#endif
