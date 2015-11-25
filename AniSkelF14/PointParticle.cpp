#include "PointParticle.h"
#include "modelerdraw.h"
#include "vec.h"


PointParticle::~PointParticle(){
	
}

PointParticle::PointParticle(const PointParticle& rhs) {
	m_fMass = rhs.m_fMass;
	m_position = rhs.m_position;
	m_velocity = rhs.m_velocity;
	forces = rhs.forces;
}

void PointParticle::Draw(){

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glPushMatrix();
	setDiffuseColor(1, 1, 1);

	glPointSize(1.0f);

	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(m_position[0], m_position[1], m_position[2]);
	glEnd();
	// printf("draw: %f, %f, %f\n", m_position[0], m_position[1], m_position[2]);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}

Particle* PointParticle::DeepCopy(){
	// i don't know how to copy la
	Particle* n_p = new PointParticle();
	n_p->setMass(m_fMass);
	n_p->setPosition(Vec3f(m_position[0], m_position[1], m_position[2]));
	n_p->setVelocity(Vec3f(m_velocity[0], m_velocity[1], m_velocity[2]));
	return n_p;
}

PointParticle& PointParticle::operator=(const PointParticle& rhs) {
	if (this != &rhs) {
		m_fMass = rhs.m_fMass;
		m_position = rhs.m_position;
		m_velocity = rhs.m_velocity;
		forces = rhs.forces;
	}
	return *this;
}