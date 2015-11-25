#ifndef POINT_PARTICLE_H
#define POINT_PARTICLE_H

#include "particle.h"

class PointParticle :
	public Particle
{
public:
	PointParticle() : Particle(){};
	PointParticle(const PointParticle& rhs);
	PointParticle(float mass, const Vec3f &position, const Vec3f &velocity) : Particle(mass, position, velocity){};
	~PointParticle();
	Particle* DeepCopy();
	void Draw();
	PointParticle& operator=(const PointParticle& rhs);
};

#endif