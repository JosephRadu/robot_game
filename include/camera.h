#pragma once

/**
* @Author	Joseph Radu
* @date		6th January 2017
* @brief	Cameras!
*
*/

#include "entity.h"
#include <math.h>

enum movement { C_LEFT = 37, C_RIGHT = 39, C_UP = 38, C_DOWN = 40, C_FORWARDS = 84, C_BACKWARDS = 71 };

class Camera : public Entity
{
private:
	int id = 0;
	const float fRotateSpeed = 0.08;
	const float fForwardSpeed = 0.4;
public:
	Camera();

	int ID();
	void SetID(int i);
	void Move(int iMovement);
	void Update();
};