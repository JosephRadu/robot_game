#pragma once

/**
* @Author	Joseph Radu
* @date		1st December 2016
* @brief	Drawable for openGL
*
*/

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include "entity.h"
#include <vector>

class Drawable : public Entity
{
private:
	std::vector<V3D> vertices;
	V3D scale;
public:

	Drawable();

	void Init_Cube();
	void Init_Plane();

	std::vector<V3D>& Vertices();

	V3D& Scale();

	void Draw();
};