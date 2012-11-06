/*
 * Class: Particle Bith magnetical forces
 * Author: Lucas Costa Campos
 * Date: 19/09/2012
 * 
 * Be implemented a general N-dimensional
 * particle, under the effects of a constant magnectical field 
 * 
 */
#include "particle.hpp"
#ifndef MAGNET_PARTICLE_HPP
#define MAGNET_PARTICLE_HPP

namespace Physics{

	template <unsigned int N, class T>
	class Magnet: public Particle<N,T> {

		//Magnectic field
		Vector<N,T> B;
		//Electric field
		Vector<N,T> E;
		//Magnet coeficients
		double charge;

		public:
		Magnet(): Particle<N,T>() {};
		Magnet(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _E, Vector<N,T> _B): Particle<N,T>(_pos, _vel), B(_B), E(_E) {};
		Magnet(Vector<N,T> _pos, Vector<N,T> _vel, Vector<N,T> _E, Vector<N,T> _B, double _charge ,double _dt): Particle<N,T>(_pos, _vel,_dt), E(_E), B(_B), charge(_charge){
		
			std::cout << B << std::endl;
			std::cout << _vel << std::endl;
			std::cout << E << std::endl;
			std::cout << charge << std::endl;
		};
		virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, T t) const {
			//std::cout << (E+(v^B))*charge << std::endl;
			return (E+(v^B))*charge;
		}
	};

}

#endif
