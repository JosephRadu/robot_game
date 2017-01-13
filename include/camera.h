#pragma once

/**
* @Author	Joseph Radu
* @date		6th January 2017
* @brief	Cameras!
*
*/

#include "entity.h"
#include <math.h>

/*!
\ brief Possible types of camera movement.
*/
enum movement { C_LEFT = 37, C_RIGHT = 39, C_UP = 38, C_DOWN = 40, C_FORWARD = 84, C_BACKWARD = 71 };

class Camera : public Entity
{
private:
	int id = 0; // Camera unique ID
	const float fRotateSpeed = 2; // Speed of rotation.
	const float fForwardSpeed = 80; // Strafing stpeed.
public:
	/*!
	\brief Default constructor.
	*/
	Camera();

	/*!
	\ brief Returns the unique ID of the camera.
	\ return int
	*/
	int ID();

	/*!
	\ brief Set unique ID of unit.
	\ param int
	*/
	void SetID(int i);

	/*!
	\ brief Move the camera in a direction using the movement enum.
	\ param int
	*/
	void Move(int iMovement);

	/*!
	\ brief Update the entity.
	*/
	void Update();
};