 // SAMPLE_SOLUTION

#include "particle.h"

Particle::Particle() : m_fMass(0.0), m_position(Vec3f(0, 0, 0)), m_velocity(Vec3f(0, 0, 0)), m_force(Vec3f(0, 0, 0)) {

}

Particle::Particle(float mass, const Vec3f &position, const Vec3f &velocity, const Vec3f &force) : m_fMass(mass), m_position(position), m_velocity(velocity), m_force(force) {
}
