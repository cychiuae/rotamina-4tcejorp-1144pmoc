#include "LSystem.h"


LSystem::LSystem(std::string initialString, int depth, int angle) :str(initialString), DEPTH(depth), currentDepth(0), ANGLE(angle)
{
}

void LSystem::expan(int depth) {
	if (depth > DEPTH)
		return;

	for (int i = 0; i < str.length(); i++) {
		std::string ch = str.substr(i, 1);
		if (ch.compare("X") == 0) {
			str.replace(i, 1, "D[RX]D[LX]RX");
			i += 11;
		}
	}

	expan(++depth);
}

const char * LSystem::printString() {
	std::cout << str;
	return str.c_str();
}

LSystem::~LSystem()
{
}

void LSystem::rotateLeft() {
	glRotatef(ANGLE, 1, 0, 0);
	glRotatef(ANGLE * 4, 0, 1, 0);
	glRotatef(ANGLE, 0, 0, 1);
}

void LSystem::rotateRight() {
	glRotatef(-ANGLE, 1, 0, 0);
	glRotatef(ANGLE * 4, 0, 1, 0);
	glRotatef(-ANGLE, 0, 0, 1);
}

void LSystem::drawLine() {
	glLineWidth(5);

	glBegin(GL_LINES);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);
	glEnd();

	glTranslatef(0, 0.2, 0);
}

void LSystem::push() {
	glPushMatrix();
}

void LSystem::pop() {
	glPopMatrix();
}

void LSystem::drawLSystem() {
	for (int i = 0; i < str.size(); i++) {
		std::string ch = str.substr(i, 1);
		if (ch.compare("D") == 0 || ch.compare("X") == 0) {
			drawLine();
		} else if (ch.compare("[") == 0){
			push();
		} else if (ch.compare("]") == 0){
			pop();
		} else if (ch.compare("R") == 0){
			rotateRight();
		} else if (ch.compare("L") == 0){
			rotateLeft();
		}
		
	}
}