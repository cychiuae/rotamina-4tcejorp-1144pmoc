#include "Wind.h"


Wind::Wind()
{
}


Wind::~Wind()
{
}

void Wind::setMagnitube(float m){
	m_fMagnitube = m;
}

void Wind::setDirection(Vec3f &dir) {
	m_direction = dir;
}

Vec3f Wind::getForce()
{
	return m_fMagnitube * m_direction;
}
