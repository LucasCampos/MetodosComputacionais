/*
 * Class: Harmonic oscilator
 * Author: Lucas Costa Campos
 * Date: 24/09/2012
 * 
 * ND harmonic oscilator
 * 
 */
#include "particle.hpp"
#ifndef SPRING_PARTICLE_HPP
#define SPRING_PARTICLE_HPP

namespace Physics{

	template <unsigned int N, class T>
		class Spring: public Particle<N,T> {

			//Position of equilibrium
			Vector<N,T> p0;
			//Rest Length
			double l;
			//Spring constant
			double k;

			public:
			Spring(): Particle<N,T>(), l(0), k(1.0) {};
			Spring(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _p0): Particle<N,T>(_pos, _vel), p0(_p0){};
			Spring(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _p0, double _l, double _k ,double _dt): Particle<N,T>(_pos, _vel,_dt), p0(_p0), k(_k), l(_l){
			};
			virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, double t) const {

				Vector<N,T> d = p-p0;
				T norm = d.Magnitude();
				d.Normalize();
				return -d*k*(norm-l);

			}
		};

}

#endif
