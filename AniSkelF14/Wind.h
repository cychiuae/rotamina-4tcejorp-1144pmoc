#ifndef WIND_H
#define WIND_H

#include "Force.h"
#include "vec.h"

class Wind :
	public Force
{
public:
	Wind();
	~Wind();
	void setMagnitube(float mag);
	void setDirection(Vec3f& dir);
	Vec3f getForce();
private:
	float m_fMagnitube;
	Vec3f m_direction;
	
};

#endif