#include <memory>

#ifdef WIN32
#include <windows.h>
#endif

#include <FL/Fl.H>
#include <GL/gl.h>

#include "modelerdraw.h"
#include "PointParticle.h"

using namespace std;

PointParticle::PointParticle()
{}

unique_ptr<Particle> PointParticle::Clone() const
{
	unique_ptr<PointParticle> p(new PointParticle);
	*p = *this;
	return std::move(p);
}

void PointParticle::Draw()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPushMatrix();
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(GetPos()[0], GetPos()[1], GetPos()[2]);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}