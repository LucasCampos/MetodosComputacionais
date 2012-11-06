/*
 * Class: N-Dimensional Drawable Particle
 * Author: Lucas Costa Campos
 * Date: 10/09/2012
 * 
 * Inherites from Drawable and Particle. Therefore,
 * to be implemented, a derived class must overload
 * both, Accel and Draw.
 *
 */
#ifndef DRAWABLE_PARTICLE_HPP
#define DRAWABLE_PARTICLE_HPP
#include "../Graphics/drawable.hpp"
#include <GL/glfw.h>

namespace Physics {

	template <unsigned int N, class T>
		class DrawableParticle: public Particle<N,T>, public Graphics::Drawable {
			public:
				DrawableParticle(): Particle<N,T>(), Drawable(){};
				DrawableParticle(Vector<N,T> _pos, Vector<N,T> _vel): Particle<N,T>(_pos, _vel), Drawable(){};
				DrawableParticle(Vector<N,T> _pos, Vector<N,T> _vel, double _dt): Particle<N,T>(_pos, _vel, _dt), Drawable(){};
				DrawableParticle(Vector<N,T> _pos, Vector<N,T> _vel, double _dt, double _red, double _blue, double _green): Particle<N,T>(_pos, _vel, _dt), Drawable(_red, _green, _blue) {};
		};
}

#endif
