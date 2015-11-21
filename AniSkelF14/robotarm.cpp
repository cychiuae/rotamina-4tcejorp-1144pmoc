// The sample robotarm model.  You should build a file
// very similar to this for when you make your model.
#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"
#include "LSystem.h"
#include "PointParticle.h"


#include <FL/gl.h>
#include <stdlib.h>

#define M_DEFAULT 2.0f
#define M_OFFSET 3.0f
#define P_OFFSET 0.3f
#define MAX_VEL 200
#define MIN_STEP 0.1


#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f
#define COLOR_MBLUE		0.34f, 0.6f, 0.79f
#define COLOR_GREY		0.25f, 0.25f, 0.25f
#define COLOR_WHITE     1.0f,1.0f,1.0f
#define COLOR_BLACK     0.0f,0.0f,0.0f
#define COLOR_DARK      0.17f,0.16f,0.18f
#define COLOR_YELLOW    1.0f, 1.0f, 0.0f



// This is a list of the controls for the RobotArm
// We'll use these constants to access the values 
// of the controls from the user interface.
enum RobotArmControls
{ 
    // BASE_ROTATION=0, LOWER_TILT, UPPER_TILT, CLAW_ROTATION,
    //     BASE_LENGTH, LOWER_LENGTH, UPPER_LENGTH, PARTICLE_COUNT, NUMCONTROLS, 

    XPOS,
    YPOS,
    ZPOS,
    // HEIGHT, 
    // ROTATE,
    HEAD_X_ROTATION,
    HEAD_Y_ROTATION,
    HEAD_Z_ROTATION,
    LEFT_UPPER_ARM_ROTATION_X,
    LEFT_UPPER_ARM_ROTATION_Y,
    LEFT_UPPER_ARM_ROTATION_Z,
    LEFT_FORE_ARM_ROTATION_Y,
    LEFT_FORE_ARM_ROTATION_Z,
    RIGHT_UPPER_ARM_ROTATION_X,
    RIGHT_UPPER_ARM_ROTATION_Y,
    RIGHT_UPPER_ARM_ROTATION_Z,
    RIGHT_FORE_ARM_ROTATION_Y,
    RIGHT_FORE_ARM_ROTATION_Z,
    LEFT_LEG_ROTATION,
    RIGHT_LEG_ROTATION,
    L_SYSTEM_DEPTH,
    L_SYSTEM_ANGLE,
    WHOLE_SCALE_X,
    WHOLE_SCALE_Y,
    WHOLE_SCALE_Z,
    LIGHT_POSITION_X,
    LIGHT_POSITION_Y,
    LIGHT_POSITION_Z,
    LEVEL,
    FOG,
    SHOW_WING,
    NUMCONTROLS
};

void ground(float h);
void base(float h);
void rotation_base(float h);
void lower_arm(float h);
void upper_arm(float h);
void claw(float h);
void y_box(float h);

// To make a RobotArm, we inherit off of ModelerView
class RobotArm : public ModelerView 
{
public:
    RobotArm(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) {}
    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createRobotArm(int x, int y, int w, int h, char *label)
{ 
    return new RobotArm(x,y,w,h,label); 
}

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))





// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotArm::draw()
{
	/* pick up the slider values */


	ModelerView::draw();

	// draw the sample model
	setAmbientColor(.5f, .5f, .5f);
	setDiffuseColor(COLOR_MBLUE);
	
	glPushMatrix();
		glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		glScaled(VAL(WHOLE_SCALE_X),VAL(WHOLE_SCALE_Y),VAL(WHOLE_SCALE_Z));
		
		glTranslated(0, -3, 0);
		glRotated(-90, 1.0, 0.0, 0.0);

		// body rt:
		
		
		glPushMatrix(); 
		drawTextureCylinder(2, 1.75, 2);

			if(VAL(LEVEL)>=1){

			if(VAL(SHOW_WING)){
			glPushMatrix();
			setDiffuseColor(COLOR_BLACK);
			glRotated(90,1,0,0);
			glTranslated(0,1.5,-2.1);
			glPopMatrix();				
			}


			glPushMatrix(); 
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(-0.3, 0, 1.5);
				drawCylinder(0.5, 1.8, 1.8);
			glPopMatrix();
			
			glPushMatrix(); 
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(0.3, 0, 1.5);
				drawCylinder(0.5, 1.8, 1.8);
			glPopMatrix();

			glPushMatrix(); 
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(-0.5, -2.05, 1.5);
				drawBox(1, 4.1, 0.5);
			glPopMatrix();
			}

			// head start 
			
			if(VAL(LEVEL)>=2){
			glPushMatrix(); 
				setDiffuseColor(COLOR_RED);
				glTranslated(0, 0, 2);
				glRotated(VAL(HEAD_X_ROTATION), 1.0, 0.0, 0.0);
				glRotated(VAL(HEAD_Y_ROTATION), 0.0, 0.0, 1.0);
				glRotated(VAL(HEAD_Z_ROTATION), 0.0, 1.0, 0.0);
				drawCylinder(0.25, 0.25, 0.25); // head joint 

				
				if(VAL(LEVEL)>=3){
				glPushMatrix();
					setDiffuseColor(COLOR_YELLOW);
					glTranslated(0, 0, 0.25);
					drawCylinder(2, 2, 2); // head

					if(VAL(LEVEL)>=4){

					glPushMatrix(); 

						setDiffuseColor(COLOR_YELLOW);
						glTranslated(0, 0, 2);
						drawSphere(2);    // forehead 

						// Hair 
						if(VAL(LEVEL)>=5){


						glPushMatrix();
						setDiffuseColor(COLOR_DARK);
						//1.75
						glTranslated(0, 0, -0.25);
						drawCylinder(0.5, 2.1, 2.1); // 頭巾
						glPopMatrix();

						LSystem lSystem("X", VAL(L_SYSTEM_DEPTH), VAL(L_SYSTEM_ANGLE));
						lSystem.expan(0);

						glPushMatrix(); 
							setDiffuseColor(COLOR_BLACK);
							glTranslated(0, 0, 1);
							//drawCylinder(0.6, 0.1, 0.1);
							glPushMatrix();
								glRotated(90, 1.0, 0.0, 0.0);
								lSystem.drawLSystem();
							glPopMatrix();
						glPopMatrix();
						
						glPushMatrix(); 
							setDiffuseColor(COLOR_BLACK);
							glRotated(-10, 0.0, 1.0, 0.0);
							glTranslated(0, 0, 1);
							//drawCylinder(0.6, 0.1, 0.1);
							glPushMatrix();
								glRotated(90, 1.0, 0.0, 0.0);
								lSystem.drawLSystem();
							glPopMatrix();
						glPopMatrix();
						
						glPushMatrix(); 
							setDiffuseColor(COLOR_BLACK);
							glRotated(10, 0.0, 1.0, 0.0);
							glTranslated(0, 0, 1);
							//drawCylinder(0.6, 0.1, 0.1);
							glPushMatrix();
								glRotated(90, 1.0, 0.0, 0.0);
								lSystem.drawLSystem();
							glPopMatrix();
						glPopMatrix();
						}

					glPopMatrix();
					}

					
					if(VAL(LEVEL)>=4){
					glPushMatrix(); 
						setDiffuseColor(COLOR_GREY);
						glRotated(90, 1.0, 0.0, 0.0);
						glTranslated(0.75, 2, 2);
						drawCylinder(0.25, 0.75, 0.75); // glasses 

						
						if(VAL(LEVEL)>=5){
						glPushMatrix(); 
							setDiffuseColor(COLOR_WHITE);
							glTranslated(0.0, 0.0, 0.25);
							drawCylinder(0.05, 0.6, 0.6); // eye 

							
							if(VAL(LEVEL)>=6){
							glPushMatrix(); 
								setDiffuseColor(COLOR_BLACK);
								glTranslated(0.0, 0.0, 0.05);
								drawCylinder(0.05, 0.1, 0.1); // eye pig 
							glPopMatrix();
							}

						glPopMatrix();
						}

					glPopMatrix();
					}

					
					if(VAL(LEVEL)>=4){
					glPushMatrix(); 
						setDiffuseColor(COLOR_GREY);
						glRotated(90, 1.0, 0.0, 0.0);
						glTranslated(-0.75, 2, 2);
						drawCylinder(0.25, 0.75, 0.75); // glasses 

						
						if(VAL(LEVEL)>=5){
						glPushMatrix(); 
							setDiffuseColor(COLOR_WHITE);
							glTranslated(0.0, 0.0, 0.25);
							drawCylinder(0.05, 0.6, 0.6); // eye

							
							if(VAL(LEVEL)>=6){
							glPushMatrix(); 
								setDiffuseColor(COLOR_BLACK);
								glTranslated(0.0, 0.0, 0.05);
								drawCylinder(0.05, 0.1, 0.1); // eye pig
							glPopMatrix();
							}
						glPopMatrix();
						}

					glPopMatrix();
					}

					if (VAL(LEVEL) >= 4) {
						setDiffuseColor(COLOR_BLUE);
						glPushMatrix();
						glRotated(180, 0, 0, 1);
						glTranslated(0, 1.5, 1.2);
						drawPyramid();
						glPopMatrix();
					}

					if(VAL(LEVEL)>=4){
					glPushMatrix(); 
						// Mouth
						setDiffuseColor(COLOR_BLACK);
						glTranslated(-1, -2.0, 0);
						drawBox(2, 1.5, 1);

						// Tongue
						
						if(VAL(LEVEL)>=5){
						glPushMatrix(); 
							setDiffuseColor(COLOR_RED);
							drawTriangle(0, -0.1, 0, 2, -0.1, 0, 1, -0.1, 0.5);
						glPopMatrix();

						// Tooth
						
						glPushMatrix(); 
							setDiffuseColor(COLOR_WHITE);
							glTranslated(0, -0.1, 0.75);
							drawBox(2, 0.01, 0.25);
						glPopMatrix();
						}
					glPopMatrix();
					}

				glPopMatrix();
				}

			glPopMatrix();
			
			// head end

			// left hand
			

			glPushMatrix(); 
				// arm1 start
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(-2.8, 0, 1);
				glTranslated(0, 0.25, 1.07);
				glRotated(-VAL(LEFT_UPPER_ARM_ROTATION_X), 1.0, 0.0, 0.0);
				glRotated(-VAL(LEFT_UPPER_ARM_ROTATION_Y), 0.0, 0.0, 1.0);
				glTranslated(0, -0.25, -1.07);
				drawBox(0.5, 0.5, 1.07);
				// arm joint start
				
				if(VAL(LEVEL)>=3){
				glPushMatrix(); 
					glRotated(VAL(LEFT_UPPER_ARM_ROTATION_Z), 0.0, 1.0, 0.0);
					setDiffuseColor(COLOR_RED);
					glTranslated(0.25, 0.25, -0.13);
					drawCylinder(0.13, 0.125, 0.125);
					// arm2 start
					
					if(VAL(LEVEL)>=4){
					glPushMatrix(); 
						glRotated(-VAL(LEFT_FORE_ARM_ROTATION_Y), 0.0, 0.0, 1.0);
						glRotated(VAL(LEFT_FORE_ARM_ROTATION_Z), 0.0, 1.0, 0.0);
						setDiffuseColor(COLOR_YELLOW);
						glTranslated(0, 0, -0.53);
						drawCylinder(0.53, 0.17, 0.17);
						// hand start
						
						if(VAL(LEVEL)>=5){
						glPushMatrix(); 
							setDiffuseColor(COLOR_BLACK);
							glTranslated(0, 0, -0.13);
							drawSphere(0.27);
						glPopMatrix();
						}
					// hand end
					glPopMatrix();
					}
				// arm2 end
				glPopMatrix();
				}
				// arm joint end
				// arm1 end
			glPopMatrix();
			
			// left hand end

			// right hand start
			

			glPushMatrix(); 
				// arm1 start
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(2.3, 0, 1);
				glTranslated(0, 0.25, 1.07);
				glRotated(-VAL(RIGHT_UPPER_ARM_ROTATION_X), 1.0, 0.0, 0.0);
				glRotated(VAL(RIGHT_UPPER_ARM_ROTATION_Y), 0.0, 0.0, 1.0);
				glTranslated(0, -0.25, -1.07);
				drawBox(0.5, 0.5, 1.07);
				// arm joint start
				
				if(VAL(LEVEL)>=3){
				glPushMatrix(); 
					glRotated(-VAL(RIGHT_UPPER_ARM_ROTATION_Z), 0.0, 1.0, 0.0);
					setDiffuseColor(COLOR_RED);
					glTranslated(0.25, 0.25, -0.13);
					drawCylinder(0.13, 0.125, 0.125);
					// arm2 start
					
					if(VAL(LEVEL)>=4){
					glPushMatrix(); 
						glRotated(VAL(RIGHT_FORE_ARM_ROTATION_Y), 0.0, 0.0, 1.0);
						glRotated(-VAL(RIGHT_FORE_ARM_ROTATION_Z), 0.0, 1.0, 0.0);
						setDiffuseColor(COLOR_YELLOW);
						glTranslated(0, 0, -0.53);
						drawCylinder(0.53, 0.17, 0.17);
					// hand start
					
					glPushMatrix(); 
						setDiffuseColor(COLOR_BLACK);
						glTranslated(0, 0, -0.13);
						drawSphere(0.27);
					glPopMatrix();
					
					// hand end
					glPopMatrix();
					}
				// arm2 end
				glPopMatrix();
				}
				// arm joint end
				// arm1 end
			glPopMatrix();
			
			// right hand end

			// left leg
			

			glPushMatrix(); 
				// leg start
				setDiffuseColor(COLOR_MBLUE);
				glRotated(VAL(LEFT_LEG_ROTATION), 1.0, 0.0, 0.0);
				glTranslated(-1.0, 0, -0.6);
				drawCylinder(0.5, 0.5, 0.6);
				// shoe start
				
				if(VAL(LEVEL)>=3){
				glPushMatrix(); 
					setDiffuseColor(COLOR_BLACK);
					glTranslated(-0.5, -1.2, -0.5);
					drawBox(1.0, 1.5, 0.5);
				glPopMatrix();
				}
				// shoe end
				// leg end
			glPopMatrix();
			}

			// right leg
			
			if(VAL(LEVEL)>=2){
			glPushMatrix(); 
				// leg start
				setDiffuseColor(COLOR_MBLUE);
				glRotated(VAL(RIGHT_LEG_ROTATION), 1.0, 0.0, 0.0);
				glTranslated(1.0, 0, -0.6);
				drawCylinder(0.5, 0.5, 0.6);
				// shoe start
				
				if(VAL(LEVEL)>=3){
				glPushMatrix(); 
					setDiffuseColor(COLOR_BLACK);
					glTranslated(-0.5, -1.2, -0.5);
					drawBox(1.0, 1.5, 0.5);
				glPopMatrix();
				}
			// shoe end
			// leg end
			glPopMatrix();
			}

		glPopMatrix();
		

	glPopMatrix(); 

	//*** DON'T FORGET TO PUT THIS IN YOUR OWN CODE **/
	endDraw();
}

void ground(float h) 
{
	glDisable(GL_LIGHTING);
	glColor3f(0.65,0.45,0.2);
	glPushMatrix();
	glScalef(30,0,30);
	y_box(h);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void base(float h) {
	setDiffuseColor( 0.25, 0.25, 0.25 );
	setAmbientColor( 0.25, 0.25, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
	glScalef(4.0f, h, 4.0f);
	y_box(1.0f);
	glPopMatrix();
}

void rotation_base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glScalef(4.0, h, 4.0);
			y_box(1.0f); // the rotation base
		glPopMatrix();
		setDiffuseColor( 0.15, 0.15, 0.65 );
		setAmbientColor( 0.15, 0.15, 0.65 );
		glPushMatrix();
			glTranslatef(-0.5, h, -0.6);
			glScalef(2.0, h, 1.6);
			y_box(1.0f); // the console
		glPopMatrix();
		setDiffuseColor( 0.65, 0.65, 0.65 );
		setAmbientColor( 0.65, 0.65, 0.65 );
		glPushMatrix();
			glTranslatef( 0.5, h, 0.6 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			drawCylinder( h, 0.05, 0.05 ); // the pipe
		glPopMatrix();
	glPopMatrix();
}

void lower_arm(float h) {					// draw the lower arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	y_box(h);
}

void upper_arm(float h) {					// draw the upper arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
	glScalef( 1.0, 1.0, 0.7 );
	y_box(h);
	glPopMatrix();
}

void claw(float h) {
	setDiffuseColor( 0.25, 0.25, 0.85 );
	setAmbientColor( 0.25, 0.25, 0.85 );

	glBegin( GL_TRIANGLES );

	glNormal3d( 0.0, 0.0, 1.0);		// +z side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d(-0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);

	glNormal3d( 0.0, 0.0, -1.0);	// -z side
	glVertex3d( 0.5, 0.0, -0.5);
	glVertex3d(-0.5, 0.0, -0.5);
	glVertex3d( 0.5,   h, -0.5);

	glEnd();

	glBegin( GL_QUADS );

	glNormal3d( 1.0,  0.0,  0.0);	// +x side
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);
	glVertex3d( 0.5,   h,-0.5);

	glNormal3d( 0.0,-1.0, 0.0);		// -y side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0, 0.5);

	glEnd();
}

void y_box(float h) {

	glBegin( GL_QUADS );

	glNormal3d( 1.0 ,0.0, 0.0);			// +x side
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d( 0.25,  h, 0.25);

	glNormal3d( 0.0 ,0.0, -1.0);		// -z side
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d( 0.25,  h,-0.25);

	glNormal3d(-1.0, 0.0, 0.0);			// -x side
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,  h, 0.25);
	glVertex3d(-0.25,  h,-0.25);

	glNormal3d( 0.0, 0.0, 1.0);			// +z side
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0, 1.0, 0.0);			// top (+y)
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0,-1.0, 0.0);			// bottom (-y)
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d( 0.25,0.0,-0.25);

	glEnd();
}

int main()
{
    ModelerControl controls[NUMCONTROLS ];

	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);

	controls[HEAD_X_ROTATION] = ModelerControl("Head X Rotate", -5, 5, 1, 0);
	controls[HEAD_Y_ROTATION] = ModelerControl("Head Y Rotate", -90, 90, 1, 0);
	controls[HEAD_Z_ROTATION] = ModelerControl("Head Z Rotate", -5, 5, 1, 0);

	controls[LEFT_UPPER_ARM_ROTATION_X] = ModelerControl("Left Upper Arm Rotation X", -70, 170, 1, 0);
	controls[LEFT_UPPER_ARM_ROTATION_Y] = ModelerControl("Left Upper Arm Rotation Y", -30, 30, 1, 0);
	controls[LEFT_UPPER_ARM_ROTATION_Z] = ModelerControl("Left Upper Arm Rotation Z", 0, 36, 1, 0);
	controls[LEFT_FORE_ARM_ROTATION_Y] = ModelerControl("Left Fore Arm Rotation Y", -60, 60, 1, 0);
	controls[LEFT_FORE_ARM_ROTATION_Z] = ModelerControl("Left Fore Arm Rotation Z", -150, 0, 1, 0);

	controls[RIGHT_UPPER_ARM_ROTATION_X] = ModelerControl("Right Upper Arm Rotation X", -70, 170, 1, 0);
	controls[RIGHT_UPPER_ARM_ROTATION_Y] = ModelerControl("Right Upper Arm Rotation Y", -30, 30, 1, 0);
	controls[RIGHT_UPPER_ARM_ROTATION_Z] = ModelerControl("Right Upper Arm Rotation Z", 0, 36, 1, 0);
	controls[RIGHT_FORE_ARM_ROTATION_Y] = ModelerControl("Right Fore Arm Rotation Y", -60, 60, 1, 0);
	controls[RIGHT_FORE_ARM_ROTATION_Z] = ModelerControl("Right Fore Arm Rotation Z", -150, 0, 1, 0);

	controls[LEFT_LEG_ROTATION] = ModelerControl("Left Leg Rotation", -15, 15, 1, 0);
	controls[RIGHT_LEG_ROTATION] = ModelerControl("Right Leg Rotation", -15, 15, 1, 0);

	controls[L_SYSTEM_DEPTH] = ModelerControl("L System Depth", 1, 8, 1, 0);
	controls[L_SYSTEM_ANGLE] = ModelerControl("L System Angle", 20, 100, 1, 0);

	controls[WHOLE_SCALE_X] = ModelerControl("Whole Scale X", 0.1, 1, 0.1, 1);
	controls[WHOLE_SCALE_Y] = ModelerControl("Whole Scale Y", 0.1, 1, 0.1, 1);
	controls[WHOLE_SCALE_Z] = ModelerControl("Whole Scale Z", 0.1, 1, 0.1, 1);

	controls[LIGHT_POSITION_X] = ModelerControl("Light Position X", -30, 30, 1, 4);
	controls[LIGHT_POSITION_Y] = ModelerControl("Light Position Y", -30, 30, 1, 2);
	controls[LIGHT_POSITION_Z] = ModelerControl("Light Position Z", -30, 30, 1, -4);

	controls[LEVEL] = ModelerControl("LEVEL OF DETAILS", 1, 6, 1, 6);
	controls[FOG] = ModelerControl("Fog Intensity", 0, 2, 0.5, 0);
	controls[SHOW_WING] = ModelerControl("Show the batman wing", 0, 1, 1, 0);

	// You should create a ParticleSystem object ps here and then
	// call ModelerApplication::Instance()->SetParticleSystem(ps)
	// to hook it up to the animator interface.

	// ParticleSystem *ps = new ParticleSystem();

	// Force* gravity = new Gravity(9.81);
	// ModelerApplication::Instance()->SetParticleSystem(ps);
	// for (int i = 0; i < 100; i++)
	// {
	// 	float mass = 1.0f;
	// 	Particle *p = new PointParticle(mass, Vec3f(0, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 0, 0));
	// 	ps->addParticle(p);
	// 	ps->addForce(gravity);

	// }

    ModelerApplication::Instance()->Init(&createRobotArm, controls, NUMCONTROLS);

    return ModelerApplication::Instance()->Run();
}
