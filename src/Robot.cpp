#ifdef _WINDOWS
#include <windows.h>
#endif
#define PI 3.14159
#include <gl/gl.h>
#include <gl/glu.h>

#include "Robot.h"

Robot::Robot()
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	movementState = MOVEMENT_STATIC;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	bInitialMovement = false;

	v3dPosition.set(0, 0, 0);
	v3dDirection.set(0, 0, 1);

	fAngle = 0;



}

Robot::~Robot()
{
}

void Robot::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);	// top face
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// front face
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// right face
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// back face
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);	// red
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);	// white
	glTranslatef(xPos, yPos, zPos);
	glScalef(2.0f, 2.0f, 2.0f);		// head is a 2x2x2 cube
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);	// blue
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 5.0f, 2.0f);		// torso is a 3x5x2 cube
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	// draw the foot
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	DrawFoot(0.0f, -5.0f, 0.0f);
	glPopMatrix();

	glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
	glColor3f(1.0f, 1.0f, 0.0f);	// yellow
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();

}

void Robot::DrawFoot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 0.5f, 3.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawRobot()
{
	
	glPushMatrix();
	glTranslatef(v3dPosition.x(), v3dPosition.y(), v3dPosition.z());	// draw robot at desired coordinates
	glRotatef(180 + fAngle, 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
	

	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);

	// move the left arm away from the torso and rotate it to give "walking" effect
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawArm(2.5f, 0.0f, -0.5f);
	glPopMatrix();

	// move the right arm away from the torso and rotate it to give "walking" effect
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();

	// move the left leg away from the torso and rotate it to give "walking" effect
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.5f, -5.0f, -0.5f);
	glPopMatrix();

	// move the right leg away from the torso and rotate it to give "walking" effect
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawLeg(1.5f, -5.0f, -0.5f);
	glPopMatrix();
	
	glPopMatrix();	// pop back to original coordinate system
}

void Robot::AnimationPrepare(float dt)
{

}

void Robot::Move(int i)
{
	if (i == 1) {
		v3dPosition.set(v3dPosition.x() + (v3dDirection.x() *( fSpeedMovement * fTimeScale)), v3dPosition.y(), v3dPosition.z() + (v3dDirection.z() * (fSpeedMovement * fTimeScale)));
	}
}

void Robot::AnimationMove(int i) {
	switch (i)
	{
		// We have let go of our key, tell the robot to stop moving.
	case 0:
		movementState = MOVEMENT_STATIC;
		bInitialMovement = false;
		break;
	case 1:

		// We tell the robot which parts to move in what direction when we give it an initial command.
		if (!bInitialMovement) {
			legStates[LEFT] = FORWARD_STATE;
			legStates[RIGHT] = BACKWARD_STATE;
			armStates[LEFT] = FORWARD_STATE;
			armStates[RIGHT] = BACKWARD_STATE;
			bInitialMovement = true;
		}

		movementState = MOVEMENT_FORWARDS;

		break;

	case 2:
		// We tell the robot which parts to move in what direction when we give it an initial command.
		if (!bInitialMovement) {
			legStates[LEFT] = BACKWARD_STATE;
			legStates[RIGHT] = FORWARD_STATE;
			armStates[LEFT] = BACKWARD_STATE;
			armStates[RIGHT] = FORWARD_STATE;
			bInitialMovement = true;
		}

		movementState = MOVEMENT_FORWARDS;
		break;
	}
}

void Robot::Update(float dt)
{
	fTimeScale = dt;
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{

		// If the robot needs to settle we have to bring all limbs back into position.
		if (movementState == MOVEMENT_STATIC) {

			if (legAngles[side] > 0) {
				legStates[side] = BACKWARD_STATE;
			}
			else if (legAngles[side] < 0) {
				legStates[side] = FORWARD_STATE;
			}

			// Snap it to 0 degrees if it's close to stop jittering.
			if (legAngles[side] < 1.5 && legAngles[side] > -1.5) {
				legAngles[side] = 0;
				legStates[side] = STATIC_STATE;
			}

			if (armAngles[side] > 0) {
				armStates[side] = BACKWARD_STATE;
			}
			else if (armAngles[side] < 0) {
				armStates[side] = FORWARD_STATE;
			}

			// Snap it to 0 degrees if it's close to stop jittering.
			if (armAngles[side] < 1.5 && armAngles[side] > -1.5) {
				armAngles[side] = 0;
				armStates[side] = STATIC_STATE;
			}
		}


		if (movementState == MOVEMENT_FORWARDS) {
			// change state if exceeding angles
			if (armAngles[side] >= 20.0f)
				armStates[side] = BACKWARD_STATE;
			else if (armAngles[side] <= -20.0f)
				armStates[side] = FORWARD_STATE;

			// change state if exceeding angles
			if (legAngles[side] >= 15.0f)
				legStates[side] = BACKWARD_STATE;
			else if (legAngles[side] <= -15.0f)
				legStates[side] = FORWARD_STATE;
		}



		// Always update the movement of arms and legs.
		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += fSpeedLeg * fTimeScale;
		else
			legAngles[side] -= fSpeedLeg * fTimeScale;

		// arms
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += fSpeedArm * fTimeScale;
		else
			armAngles[side] -= fSpeedArm * fTimeScale;
	}
}

float Robot::angle()
{
	return fAngle;
}

void Robot::angle(float f)
{
	fAngle = f;
}

void Robot::rotate(float f)
{
	fAngle += f;

	if (fAngle < 0)
		fAngle = 359.0f;

	if (fAngle >= 360.0f)
		fAngle = 0.0f;

	v3dDirection.setX(sin(PI * fAngle / 180) * ( 1 * fTimeScale));
	v3dDirection.setZ(cos(PI * fAngle / 180) * ( 1 * fTimeScale));
}
