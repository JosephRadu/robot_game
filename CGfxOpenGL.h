#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0


#include <iostream>

class Robot;

class CGfxOpenGL
{
private:
	Robot *theRobot;
	float rotationAngle;

	bool bPaused;



	int m_windowWidth;
	int m_windowHeight;

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void TogglePause();

	void input(int i);

	Robot robot();



};

#endif