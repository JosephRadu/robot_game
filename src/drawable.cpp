/**
* @Author	Joseph Radu
* @date		1st December 2016
* @brief	Drawable for openGL
*
*/

#include "drawable.h"

Drawable::Drawable()
{
	v3dPosition.set(0, 0, 0);
	v3dRotation.set(0, 0, 0);
	scale.set(0, 0, 0);
	colour.set(0.3, 0.3, 0.3);
	iAngle = 0;
}

std::vector<V3D>& Drawable::Vertices()
{
	return vertices;
}

void Drawable::Init_Cube()
{
	vertices.clear();
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// top face
	vertices.push_back(V3D(0.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, 0.0f, 0.0f));
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// front face
	vertices.push_back(V3D(-1.0f, 0.0f, 0.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, 0.0f));
	vertices.push_back(V3D(0.0f, -1.0f, 0.0f));
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// right face
	vertices.push_back(V3D(0.0f, -1.0f, 0.0f));
	vertices.push_back(V3D(0.0f, -1.0f, -1.0f));
	vertices.push_back(V3D(0.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, 0.0f, 0.0f));	// left face
	vertices.push_back(V3D(-1.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, 0.0f));
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// bottom face
	vertices.push_back(V3D(0.0f, -1.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, 0.0f));
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// back face
	vertices.push_back(V3D(-1.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, -1.0f, -1.0f));
	vertices.push_back(V3D(0.0f, -1.0f, -1.0f));
	std::reverse(vertices.begin(), vertices.end());
}
void Drawable::Init_Plane()
{
	vertices.clear();
	vertices.push_back(V3D(0.0f, 0.0f, 0.0f));	// top face
	vertices.push_back(V3D(0.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, 0.0f, -1.0f));
	vertices.push_back(V3D(-1.0f, 0.0f, 0.0f));
	std::reverse(vertices.begin(), vertices.end());
}

void Drawable::Draw()
{
	glPushMatrix();
	glTranslatef(v3dPosition.x(), v3dPosition.y(), v3dPosition.z());
	glRotatef(iAngle, v3dRotation.x(), v3dRotation.y(), v3dRotation.z());	// rotate the drawable on its y-axis
	glColor3f(colour.x(), colour.y(), colour.z());
	glScalef(scale.x(), scale.y(), scale.z());
	glBegin(GL_POLYGON);

	for (auto & i : vertices) {
		glVertex3f(i.x(), i.y(), i.z());
	}
	glEnd();
	glPopMatrix();
	
}

V3D& Drawable::Scale()
{
	return scale;
}

void Drawable::Update(float dt)
{

}

V3D& Drawable::Colour()
{
	return colour;
}