#pragma once
#include "Force.h"
#include "vec.h"

class Gavity : public Force
{
private:
	float G;
public:
	Gavity(float const_g);
	~Gavity();
	void setConstant(float const_g);
	Vec3f getState(Particle* p);
};

