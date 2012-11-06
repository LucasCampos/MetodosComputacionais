/*
 * Class: N-Dimensional Particle
 * Author: Lucas Costa Campos
 * Date: 05/10/2012
 * Version 2
 * 
 * Template representing a particle. The following algorithms
 * were implemented:
 * Runge-Kutta of 1st order
 * Runge-Kutta of 2st order
 * Runge-Kutta of 4st order
 * Velocity Verlet
 * 
 * It is expected that a child class overload the Accel method.
 * This method dictates the acceleration felt by the particle at (p, v)
 */
#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "myVector.hpp"

namespace Physics {
	template <unsigned int N, class T>
		class Particle {
			private:
				T dt;
				T t;
			public:
				Vector<N,T> pos;
				Vector<N,T> vel;

				Particle(): dt(1e-2), t(0) {};
				Particle(Vector<N,T> _pos, Vector<N,T> _vel): dt(1e-2), pos(_pos), vel(_vel), t(0){};
				Particle(Vector<N,T> _pos, Vector<N,T> _vel, T _dt): dt(_dt), pos(_pos), vel(_vel), t(0){};

				virtual Vector<N,T> Accel(const Vector<N,T>& p, const Vector<N,T>& v, T t) const =0;

				void RK1() {
					Vector<N,T> oldVel = vel;
					vel += Accel(pos,vel, t)*dt;
					pos += oldVel*dt;
					t+=dt;

				}

				void RK2(){

					Vector<N,T> an = Accel(pos, vel, t);
					Vector<N,T> vm = vel+an*dt*0.5;
					Vector<N,T> xm = pos+vel*dt*0.5;
					Vector<N,T> am = Accel(xm,vm, t+dt/2);

					vel+=am*dt;
					pos+=vm*dt;
					t+= dt;
				}

				void RK4(){

					Vector<N,T> k1v = Accel(pos, vel,t)*dt;
					Vector<N,T> k1x = vel*dt;

					Vector<N,T> k2v = Accel(pos+k1x*0.5, vel+k1v*0.5, t+dt/2.0)*dt;
					Vector<N,T> k2x = (vel+k1v*0.5)*dt;

					Vector<N,T> k3v = Accel(pos+k2x*0.5, vel+k2v*0.5, t+dt/2.0)*dt;
					Vector<N,T> k3x = (vel+k2v*0.5)*dt;

					Vector<N,T> k4v = Accel(pos+k3x*0.5, vel+k3v*0.5, t+dt)*dt;
					Vector<N,T> k4x = (vel+k3v*0.5)*dt;

					vel+=(k1v+(k2v+k3v)*2+k4v)*(1.0/6.0);
					pos+=(k1x+(k2x+k3x)*2+k4x)*(1.0/6.0);
					t+=dt;
				}


				void VelocityVerlet(){

					static Vector<N,T> currAcc = Accel(pos,vel, t)*0.5*dt;
					pos += vel*dt + currAcc*dt;
					Vector<N,T> nextAcc = Accel(pos,vel,t+dt)*dt*0.5;
					vel+=nextAcc+currAcc;
					currAcc = nextAcc;

					t+=dt;
				};

		};
}
#endif
