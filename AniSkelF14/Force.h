#pragma once

#include "particle.h"
#include "vec.h"

class Force
{
public:
	Force();
	~Force();
	virtual Vec3f getState(Particle* particle)=0;
};

