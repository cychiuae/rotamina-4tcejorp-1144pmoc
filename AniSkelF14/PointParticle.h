#ifndef POINT_PARTICLE_H_
#define POINT_PARTICLE_H_

#include <memory>

#include "particle.h"

class PointParticle : public Particle
{
public:
	PointParticle(const Vec3f &pos, const float mass, const Vec3f &velocity)
		: Particle(pos, mass, velocity)
	{}
	PointParticle(const Vec3f &pos, const float mass)
		: Particle(pos, mass)
	{}

	std::unique_ptr<Particle> Clone() const override;

	void Draw() override;

protected:
	PointParticle();
};

#endif /* POINT_PARTICLE_H_ */