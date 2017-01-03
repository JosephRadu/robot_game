#pragma once

/**
* @Author	Joseph Radu
* @date		3rd January 2017
* @brief	Entity. Velocity, position and angles.
*
*/

#include "v3d.h"

class Entity
{
protected:
	V3D v3dPosition;
	V3D v3dRotation;
	int iAngle;
public:
	V3D& Position();
	V3D& Rotation();
	void AddAngle(int i);
	void SetAngle(int i);
	int Angle();
};