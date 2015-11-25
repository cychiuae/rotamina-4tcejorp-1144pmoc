#ifndef FORCE_H_
#define FORCE_H_

#include "vec.h"

class Particle;

class Force
{
public:
	Force();
	~Force();
	virtual Vec3f getForce()=0;
};

#endif
