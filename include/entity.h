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
	float fTimeScale;
	int iAngle;
public:

	/*!
	\ brief Retrieve a reference to the V3D of the entities' position.
	\ return V3D Reference
	*/
	V3D& Position();

	/*!
	\ brief Retrieve a reference to the V3D of the entities' rotation.
	\ return V3D Reference
	*/
	V3D& Rotation();

	/*!
	\ brief Retrieve a reference to the V3D of the entities' direction.
	\ return V3D Reference
	*/
	V3D& Direction();

	/*!
	\ brief Add to the angle variable.
	\ param int
	*/
	void AddAngle(int i);

	/*!
	\ brief Set the angle variable.
	\ param int
	*/
	void SetAngle(int i);

	/*!
	\ brief Return the angle variable.
	\ return int
	*/
	int Angle();


	/*!
	\ brief Set the timescale
	\ param float
	*/
	void SetTimeScale(float dt);

	/*!
	\ brief Return the timescale
	\ return float
	*/
	float TimeScale();

	/*!
	\brief Update the entity.
	\ param float timescale
	*/
	virtual void Update(float dt) = 0;
};