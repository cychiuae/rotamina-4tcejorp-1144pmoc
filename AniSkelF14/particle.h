 // SAMPLE_SOLUTION

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec.h"

class Particle {
public:
	Particle();
	Particle(float mass, const Vec3f &position, const Vec3f &velocity);
private:
	float m_fMass;
	Vec3f m_position;
	Vec3f m_velocity;
};

#endif