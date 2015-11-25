 // SAMPLE_SOLUTION

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "vec.h"
#include "Force.h"


#include <memory>
#include <vector>

#include "force.h"
#include "vec.h"

class Particle
{
public:
	Particle(const Vec3f &pos, const float mass, const Vec3f &velocity);
	Particle(const Vec3f &pos, const float mass)
		: Particle(pos, mass, Vec3f())
	{}
	virtual ~Particle();

	Particle& operator=(const Particle &rhs);

	virtual std::unique_ptr<Particle> Clone() const = 0;

	virtual void Evaluate(
		const std::vector<std::unique_ptr<Force>> &global_forces,
		const float delta_t);
	virtual void Draw() = 0;

	virtual void PushForce(std::unique_ptr<Force> &&f);

	const Vec3f& GetPos() const
	{
		return m_pos;
	}

	float GetMass() const
	{
		return m_mass;
	}

	const Vec3f& GetVelocity() const
	{
		return m_velocity;
	}

protected:
	Particle();

private:
	Vec3f m_pos;
	float m_mass;
	Vec3f m_velocity;
	// Forces specific to this particle, global forces should be added to
	// ParticleSystem instead
	std::vector<std::unique_ptr<Force>> m_forces;
};

#endif