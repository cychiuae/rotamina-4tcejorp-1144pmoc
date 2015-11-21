#include "Gavity.h"


Gavity::Gavity(float G)
{

}


Gavity::~Gavity()
{
}

void Gavity::setConstant(float const_g){
	G = const_g;
}

Vec3f Gavity::getState(Particle* p)
{
	return Vec3f(0.0f, -G, 0.0f);
}
