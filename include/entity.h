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
	V3D v3dDirection;
	int iAngle;
public:
	V3D& Position();
	V3D& Rotation();
	V3D& Direction();
	void AddAngle(int i);
	void SetAngle(int i);
	int Angle();

	/*!
	\brief Update the entity.
	*/
	virtual void Update() = 0;
};