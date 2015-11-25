#ifdef _MSC_VER
#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)
#endif

#include <cstdlib>

#include <memory>

#include <FL/gl.h>
#include "mat.h"
#include "force.h"
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particle.h"
#include "particleSystem.h"
#include "PointParticle.h"

#define M_DEFAULT 2.0f
#define M_OFFSET 3.0f
#define P_OFFSET 0.3f
#define MAX_VEL 200
#define MIN_STEP 0.1

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

// This is a list of the controls for the RobotArm
// We'll use these constants to access the values
// of the controls from the user interface.



class GlUtils
{
public:
	static Mat4f GetModelViewMatrix() {
		GLfloat m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		Mat4f matMV(m[0], m[1], m[2], m[3],
			m[4], m[5], m[6], m[7],
			m[8], m[9], m[10], m[11],
			m[12], m[13], m[14], m[15]);
		return matMV.transpose(); 
	}
	static Vec3f GetWorldPos(const Mat4f &camera_mat, const Vec3f &local_pos) {
		const Mat4f &world_mat = camera_mat.inverse() * GetModelViewMatrix();
		return world_mat * local_pos;
	}
};
enum SampleModelControls
{
	XPOS, YPOS, ZPOS, HEIGHT, ROTATE, ANGLE, PRESSURE, DENSITY, NUMCONTROLS
};

// To make a SampleModel, we inherit off of ModelerView
class SimpleTank : public ModelerView
{
public:
	SimpleTank(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSimpleTank(int x, int y, int w, int h, char *label)
{
	return new SimpleTank(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SimpleTank
void SimpleTank::draw()
{
	// This call takes care of a lot of the nasty projection
	// matrix stuff.  Unless you want to fudge directly with the
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	glPushMatrix();
	glTranslated(-1.5, 0, -2);
	glScaled(3, 1, 4);
	drawBox(1, 1, 1);
	glPopMatrix();

	// draw cannon
	glPushMatrix();
	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	glTranslated(0.0, 0.0, VAL(HEIGHT));
	drawCylinder(1, 1.0, 0.9);

	glTranslated(0.0, 0.0, 0.5);
	glRotated(90 - VAL(ANGLE), 1.0, 0.0, 0.0);
	drawCylinder(4, 0.1, 0.2);
	ParticleSystem *ps = ModelerApplication::Instance()
		->GetParticleSystem();
	if (ps && ModelerApplication::Instance()->Simulating())
	{
		const int count = VAL(DENSITY);
		for (int i = 0; i < count; ++i)
		{
			const Vec3f &spawn_pt = GlUtils::GetWorldPos(GlUtils::GetModelViewMatrix(),
				Vec3f(0.3f * (float)rand() / RAND_MAX - 0.15f,
				0.3f * (float)rand() / RAND_MAX - 0.15f, 4));
			const float pressure = VAL(PRESSURE) * (1 + 0.2f * (float)rand()
				/ RAND_MAX - 0.1f);
			const float mass = 1.0f;
			Particle *p = new PointParticle(spawn_pt, mass, Vec3f(
				5.0f * (float)rand() / RAND_MAX - 2.5f,
				pressure * sin(VAL(ANGLE) * M_PI / 180.0f), pressure));
			const float gracity_a = 6.6f;
			unique_ptr<Force> gravity(new ConstantForce(
				Vec3f(0.0f, -(mass * gracity_a), 0.0f)));
			p->PushForce(std::move(gravity));
			ps->pushParticle(unique_ptr<Particle>(p));
		}
	}
	glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue,
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[ANGLE] = ModelerControl("Angle", -10, 20, 1, 0);
	controls[PRESSURE] = ModelerControl("Pressure", 2, 20, 1, 10);
	controls[DENSITY] = ModelerControl("Density", 0, 20, 1, 5);

	ModelerApplication::Instance()->SetParticleSystem(new ParticleSystem);

	ModelerApplication::Instance()->Init(&createSimpleTank, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

