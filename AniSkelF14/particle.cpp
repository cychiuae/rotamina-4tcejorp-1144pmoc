 // SAMPLE_SOLUTION

#include "particle.h"

Particle::Particle() : m_fMass(0.0), m_position(Vec3f(0, 0, 0)), m_velocity(Vec3f(0, 0, 0)) {

}

Particle::Particle(float mass, const Vec3f &position, const Vec3f &velocity) : m_fMass(mass), m_position(position), m_velocity(velocity) {
}

void Particle::computeForcesAndUpdateParticle(std::vector<Force *> forces, float delta_t) {
	Vec3f resultingForce(0.0f, 0.0f, 0.0f);
	for (std::vector<Force *>::iterator it = forces.begin(); it != forces.end(); ++it) {
		resultingForce += (*it)->getForce();
	}
	Vec3f acceleration = resultingForce / m_fMass;
	m_velocity += acceleration * delta_t;
	m_position += m_velocity * delta_t;
}
