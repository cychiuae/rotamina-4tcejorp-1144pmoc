#include "Force.h"


#include <memory>

#include "particle.h"
#include "vec.h"

ConstantForce::ConstantForce(const Vec3f &f)
	: m_force(f)
{}

ConstantForce::ConstantForce()
{}

unique_ptr<Force> ConstantForce::Clone() const
{
	unique_ptr<ConstantForce> p(new ConstantForce);
	*p = *this;
	return std::move(p);
}

Vec3f ConstantForce::GetAcceleration(const Particle &p)
{
	return m_force / p.GetMass();
}