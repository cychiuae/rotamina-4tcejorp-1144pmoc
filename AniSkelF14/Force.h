#ifndef FORCE_H_
#define FORCE_H_

#include <memory>

#include "vec.h"

class Particle;

class Force
{
public:
	virtual ~Force()
	{}

	virtual std::unique_ptr<Force> Clone() const = 0;

	virtual Vec3f GetAcceleration(const Particle &p) = 0;
};

class ConstantForce : public Force
{
public:
	explicit ConstantForce(const Vec3f &f);

	std::unique_ptr<Force> Clone() const override;

	Vec3f GetAcceleration(const Particle &p) override;

protected:
	ConstantForce();

private:
	Vec3f m_force;
};

#endif
