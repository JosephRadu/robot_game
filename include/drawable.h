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
	std::vector<V3D> vertices; // A vector of V3D vertices (storage of polygons essentially).
	V3D scale;
public:
	/*!
	\brief Default constructor.
	*/
	Drawable();

	/*!
	\brief Create a cube using the vertices.
	*/
	void Init_Cube();

	/*!
	\brief Create a plane using the vertices.
	*/
	void Init_Plane();

	/*!
	\ brief Return a reference to the vector of V3D vertices.
	\ return V3D Reference
	*/
	std::vector<V3D>& Vertices();

	/*!
	\ brief Return a reference to V3D of the entities' scale.
	\ return V3D Reference
	*/
	V3D& Scale();

	/*!
	\brief Draw function.
	*/
	void Draw();

	/*!
	\brief Entity update function.
	*/
	void Update();
};