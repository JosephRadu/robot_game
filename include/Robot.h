#ifndef __ROBOT_H
#define __ROBOT_H

#include "V3D.h"
#include <math.h>

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;
const char STATIC_STATE = 2;

// constats for the movement state of the overall robot
const char MOVEMENT_BACKWARDS = 0;
const char MOVEMENT_FORWARDS = 1;
const char MOVEMENT_STATIC = 2;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class Robot
{
private:
	char legStates[2];
	char armStates[2];

	V3D v3dPosition;

	char movementState;

	float x;
	float y;
	float z;

	float legAngles[2];
	float armAngles[2];

	float fSpeedLeg = 40.0f;
	float fSpeedArm = 45.0f;

	float fAngle = 0;

	bool bInitialMovement;

	// draws a unit cube
	void DrawCube(float xPos, float yPos, float zPos);

	// methods to draw the parts of the robot
	void DrawArm(float xPos, float yPos, float zPos);
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawTorso(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawFoot(float xPos, float yPos, float zPos);

public:

	Robot();
	virtual ~Robot();

	// draws the entire robot
	void DrawRobot();

	float angle();
	void angle(float f);
	void rotate(float f);

	void AnimationMove(int i);
	// updates the robot data
	void AnimationPrepare(float dt);


	void Move(int i);

	V3D position();

};

#endif