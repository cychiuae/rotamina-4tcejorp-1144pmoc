#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <climits>

#include <map>
#include <memory>
#include <vector>

#include "particle.h"
#include "particleSystem.h"

using namespace std;

/***************
* Constructors
***************/

ParticleSystem::ParticleSystem()
	: m_prev_t(0.0f),
	bake_fps(0.0f),
	bake_start_time(0.0f),
	bake_end_time(0.0f),
	simulate(false),
	dirty(false)
{}

/*************
* Destructor
*************/

ParticleSystem::~ParticleSystem()
{}


/******************
* Simulation fxns
******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{

	// TODO
	m_prev_t = t;
	m_particles.clear();
	clearBaked();

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float)
{

	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float)
{

	// TODO
	m_prev_t = 0.0f;
	m_particles.clear();
	clearBaked();

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	if (simulate)
	{
		const float delta_t = t - m_prev_t;
		for (auto &p : m_particles)
		{
			p->Evaluate(m_global_forces, delta_t);
		}
		bakeParticles(t);
		m_prev_t = t;
	}
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	const int key = getKey(t);
	auto it = m_baked_particles.lower_bound(key);
	if (it == m_baked_particles.end())
	{
		return;
	}

	for (auto &p : it->second)
	{
		p->Draw();
	}
}

/** Adds the current configuration of particles to
* your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t)
{
	const int key = getKey(t);
	m_baked_particles[key].clear();
	m_baked_particles[key].reserve(m_particles.size());
	for (auto &p : m_particles)
	{
		m_baked_particles[key].push_back(p->Clone());
	}
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	m_baked_particles.clear();
}

void ParticleSystem::pushParticle(unique_ptr<Particle> &&p)
{
	m_particles.push_back(std::move(p));
}

int ParticleSystem::getKey(const float t)
{
	return t * 100;
}