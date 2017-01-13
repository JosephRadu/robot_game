/**
* @Author	Joseph Radu
* @date		6th January 2017
* @brief	Cameras!
*
*/

#include "camera.h"

Camera::Camera(){

}

void Camera::Move(int iMovement)
{
	switch (iMovement)
	{
	case C_UP:
		v3dRotation.setY(v3dRotation.y() + ((fRotateSpeed * fTimeScale)));
		v3dDirection.setY(tan(v3dRotation.y()));
		break;
	case C_LEFT:
		v3dRotation.setX(v3dRotation.x() + ((fRotateSpeed * fTimeScale)));
		v3dDirection.setX(sin(v3dRotation.x()));
		v3dDirection.setZ(cos(v3dRotation.x()));
		break;
	case C_RIGHT:
		v3dRotation.setX(v3dRotation.x() - ((fRotateSpeed * fTimeScale)));
		v3dDirection.setX(sin(v3dRotation.x()));
		v3dDirection.setZ(cos(v3dRotation.x()));
		break;
	case C_DOWN:
		v3dRotation.setY(v3dRotation.y() - (fRotateSpeed * fTimeScale));
		v3dDirection.setY(tan(v3dRotation.y()));
		break;
	case C_FORWARD:
		v3dPosition.set(
			v3dPosition.x() + (v3dDirection.x() * (fForwardSpeed * fTimeScale)),
			v3dPosition.y() + (v3dDirection.y() * (fForwardSpeed * fTimeScale)),
			v3dPosition.z() + (v3dDirection.z() * (fForwardSpeed * fTimeScale))
		);
		break;
	case C_BACKWARD:
		v3dPosition.set(
			v3dPosition.x() - (v3dDirection.x() * (fForwardSpeed * fTimeScale)),
			v3dPosition.y() - (v3dDirection.y() * (fForwardSpeed * fTimeScale)),
			v3dPosition.z() - (v3dDirection.z() * (fForwardSpeed * fTimeScale))
		);
		break;
	default:
		break;
	}
}

void Camera::Update()
{

}

int Camera::ID()
{
	return id;
}

void Camera::SetID(int i)
{
	id = i;
}