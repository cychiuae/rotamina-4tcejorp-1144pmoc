 // SAMPLE_SOLUTION

#include <vector>

#include "particle.h"
#include "vec.h"

using namespace std;

Particle::Particle(const Vec3f &pos, const float mass, const Vec3f &velocity)
	: m_pos(pos),
	m_mass(mass),
	m_velocity(velocity)
{}

Particle::Particle()
	: m_mass(0.0f)
{}

Particle::~Particle()
{}

Particle& Particle::operator=(const Particle &rhs)
{
	if (this != &rhs)
	{
		m_pos = rhs.m_pos;
		m_mass = rhs.m_mass;
		m_velocity = rhs.m_velocity;
		m_forces.clear();
		m_forces.reserve(rhs.m_forces.size());
		for (auto &f : rhs.m_forces)
		{
			m_forces.push_back(f->Clone());
		}
	}
	return *this;
}

void Particle::Evaluate(const vector<unique_ptr<Force>> &global_forces,
	const float delta_t)
{
	Vec3f a;
	for (auto &f : global_forces)
	{
		a += f->GetAcceleration(*this);
	}
	for (auto &f : m_forces)
	{
		a += f->GetAcceleration(*this);
	}
	m_velocity += a * delta_t;
	m_pos += m_velocity * delta_t;
}

void Particle::PushForce(unique_ptr<Force> &&f)
{
	m_forces.push_back(std::move(f));
}
