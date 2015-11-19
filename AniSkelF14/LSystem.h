#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <FL/gl.h>
//#include "modelerglobals.h"

class LSystem
{
private:
	float ANGLE;
	
	std::string str;
	int DEPTH;
	int currentDepth;
public:
	LSystem(std::string initialString,int depth, int angle);
	void expan(int depth);
	const char * printString();
	void rotateLeft();
	void rotateRight();
	void drawLine();
	void push();
	void pop();
	void drawLSystem();
	~LSystem();
};

