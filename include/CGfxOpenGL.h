#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

#include "drawable.h"
#include <iostream>

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "Robot.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Robot;

using namespace std;

class CGfxOpenGL
{
private:
	Robot *theRobot;
	float rotationAngle;

	bool bPaused;

	Drawable cube;

	Entity camera;

	int m_windowWidth;
	int m_windowHeight;

	int GetNextSlashes(istringstream& parserIn);

	void UpdateCamera();


	float angle = 0.0;
	// actual vector representing the camera's direction
	float lx = 0.0f, ly = 0.0f, lz = -1.0f;
	// XZ position of the camera
	float x = 0.0f, y = 0.0f, z = 0.0f;

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void TogglePause();

	void OBJRead(std::string s);

	void input(char s);

	Robot robot();



};

#endif