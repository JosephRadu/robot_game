/**
* @Author	Joseph Radu
* @date		3rd January 2017
* @brief	Entity. Velocity, position and angles.
*
*/

#include "entity.h"

V3D& Entity::Position()
{
	return v3dPosition;
}

V3D& Entity::Rotation()
{
	return v3dRotation;
}

V3D& Entity::Direction()
{
	return v3dDirection;
}

void Entity::AddAngle(int i)
{
	iAngle += i;
}

void Entity::SetAngle(int i)
{
	iAngle = i;
}

int Entity::Angle()
{
	return iAngle;
}

void Entity::SetTimeScale(float dt)
{
	fTimeScale = dt;
}

float Entity::TimeScale()
{
	return fTimeScale;
}