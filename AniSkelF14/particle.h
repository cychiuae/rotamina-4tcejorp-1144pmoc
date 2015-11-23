 // SAMPLE_SOLUTION

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "vec.h"
#include "Force.h"


class Particle {
public:
	Particle();
	Particle(float mass, const Vec3f &position, const Vec3f &velocity);
	float getMass(){ return m_fMass; }
	Vec3f getPosition(){ return m_position; }
	Vec3f getVelocity(){ return m_velocity; }
	virtual void Draw() = 0;
	virtual Particle* DeepCopy() = 0;
	void setMass(float mass){ m_fMass = mass; }
	void setPosition(Vec3f position){ m_position = position; }
	void setVelocity(Vec3f velocity){ m_velocity = velocity; }
	void addForce(Force* f) { forces.push_back(f); }
protected:
	float m_fMass;
	Vec3f m_position;
	Vec3f m_velocity;
	std::vector<Force *> forces;
};

#endif