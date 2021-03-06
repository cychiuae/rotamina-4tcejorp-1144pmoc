#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <assert.h>
#include <math.h>
#include <limits.h>


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() : bake_fps(0.0f), bake_start_time(0.0f), bake_end_time(0.0f), m_t0(0.0f), simulate(false), dirty(false)
{

}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO

}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    
	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.

	bake_start_time = 0.0f;
	m_t0 = 0.0f;

	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;
}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	bake_start_time = 0.0f;
	m_t0 = 0.0f;
	simulate = false;
	dirty = true;
	clearBaked();

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	if(simulate){
			const float delta_t = t - m_t0;
			for (auto &p : m_particles) {

				/*Vec3f force = Vec3f(0.0f, 0.0f, 0.0f);
				Vec3f velocity = p->getVelocity();
				Vec3f position = p->getPosition();
				for(auto &f : m_forces)
					force += f->getForce()*p->getMass();

				velocity += force / p->getMass() * delta_t;
				position += velocity * delta_t;
				// printf("force: %f,%f,%f \n",force[0],force[1],force[2]);
				// printf("velocity: %f,%f,%f \n",velocity[0],velocity[1force],velocity[2]);
				// printf("position: %f,%f,%f \n",position[0],position[1],position[2]);
				p->setVelocity(velocity);
				p->setPosition(position);*/
				p->computeForcesAndUpdateParticle(m_forces, delta_t);

			}
			m_t0 = t;
			bakeParticles(t);
	}
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (simulate) {
		for (vector<Particle*>::iterator bp = m_baked_particles[t].begin(); bp != m_baked_particles[t].end(); bp++) {
			(*bp)->Draw();
		}
	}
	
}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	m_baked_particles[t].clear();
	for (auto &p : m_particles) {
		m_baked_particles[t].push_back(p->DeepCopy());
	}
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	m_baked_particles.clear();
}


void ParticleSystem::addParticle(Particle* p){
	m_particles.push_back(p);
}
void ParticleSystem::addForce(Force* f){
	m_forces.push_back(f);
}




