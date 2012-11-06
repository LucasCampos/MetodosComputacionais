/*
 * Class: Particle with drag forces
 * Author: Lucas Costa Campos
 * Date: 10/09/2012
 * 
 * First its is implemented a general N-dimensional
 * particle, under the effects of drag. 
 * 
 * Second, we have a 3D particle under the effect of 
 * both, gravity and drag.
 * 
 */
#include "particle.hpp"
#ifndef DRAG_PARTICLE_HPP
#define DRAG_PARTICLE_HPP

namespace Physics{

	template <unsigned int N, class T>
	class Drag: public Particle<N,T> {

		//protected:
		//Rotation Speed
		Vector<N,T> w;
		//Drag coeficients
		double dragLinear, dragRot;

		public:
		Drag(): Particle<N,T>() {};
		Drag(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _w): Particle<N,T>(_pos, _vel), w(_w) {};
		Drag(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _w, double _dragLinear, double _dragRot ,double _dt): Particle<N,T>(_pos, _vel,_dt), w(_w), dragLinear(_dragLinear), dragRot(_dragRot){};
		virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, T t) const {
			return -v*dragLinear*v.Magnitude()+(w^v)*dragRot;
		}
	};

	class Obliquous: public Drag<3,double>{

		private:

			Vector3D g;

		public:

			Obliquous(): Drag() {g.SetElem(2,-9.8);};
			Obliquous(Vector3D _pos, Vector3D _vel, Vector3D _w): Drag(_pos,_vel,_w) {g.SetElem(2,-9.8);};
			Obliquous(Vector3D _pos, Vector3D _vel, Vector3D _w, double _dragLinear, double _dragRot ,double _dt): Drag(_pos,_vel,_w, _dragLinear, _dragRot, _dt) {g.SetElem(2,-9.8);};
				virtual Vector3D Accel(const Vector3D& p, const Vector3D& v, double t) const {
				return g+Drag::Accel(p,v);
			}

	};

}

#endif
