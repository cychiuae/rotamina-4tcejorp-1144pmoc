#pragma once
#include "particle.h"
class PointParticle :
	public Particle
{
public:
	PointParticle() : Particle(){};
	PointParticle(float mass, const Vec3f &position, const Vec3f &velocity, const Vec3f & force) : Particle(mass, position, velocity, force){};
	~PointParticle();
	Particle* DeepCopy();
	void Draw();

};

