#include "PointParticle.h"
#include "modelerdraw.h"
#include "vec.h"


PointParticle::~PointParticle(){
};

void PointParticle::Draw(){

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glPushMatrix();
	glPointSize(1.0f);

	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(getPosition()[0], getPosition()[1], getPosition()[2]);
	glEnd();

	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
};

Particle* PointParticle::DeepCopy(){
	// i don't know how to copy la
	Particle* n_p = new PointParticle();
	n_p->setMass(m_fMass);
	n_p->setPosition(Vec3f(m_position[0], m_position[1], m_position[2]));
	n_p->setVelocity(Vec3f(m_velocity[0], m_velocity[1], m_velocity[2]));
	n_p->setForce(Vec3f(m_force[0], m_force[1], m_force[2]));
	return n_p;
};