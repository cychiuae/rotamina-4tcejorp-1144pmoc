 // SAMPLE_SOLUTION

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec.h"

class Particle {
public:
	Particle();
	Particle(float mass, const Vec3f &position, const Vec3f &velocity, const Vec3f & force);
	float getMass(){ return m_fMass; };
	Vec3f getPosition(){ return m_position; };
	Vec3f getVelocity(){ return m_velocity; };
	Vec3f getForce(){ return m_force; };
	virtual void Draw() = 0;
	virtual Particle* DeepCopy() = 0;
	void setMass(float mass){ m_fMass = mass; };
	void setPosition(Vec3f position){ m_position = position; };
	void setVelocity(Vec3f velocity){ m_velocity = velocity; };
	void setForce(Vec3f force){ m_force = force; };
protected:
	float m_fMass;
	Vec3f m_position;
	Vec3f m_velocity;
	Vec3f m_force;
	
};

#endif