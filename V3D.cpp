#include "V3D.h"

V3D::V3D()
{
	fData[0] = 0;
	fData[1] = 0;
	fData[2] = 0;
}

V3D::V3D(float allValues)
{
	fData[0] = allValues;
	fData[1] = allValues;
	fData[2] = allValues;
}

V3D::V3D(float x, float y, float z)
{
	fData[0] = x;
	fData[1] = y;
	fData[2] = z;
}

void V3D::setX(float x)
{
	fData[0] = x;
}
void V3D::setY(float y)
{
	fData[1] = y;
}
void V3D::setZ(float z)
{
	fData[2] = z;
}
void V3D::set(float x, float y, float z)
{
	fData[0] = x;
	fData[1] = y;
	fData[2] = z;
}
void V3D::set(V3D vector)
{
	fData[0] = vector.x();
	fData[1] = vector.y();
	fData[2] = vector.z();
}


float V3D::x() const
{
	return fData[0];
}

float V3D::y() const
{
	return fData[1];
}

float V3D::z() const
{
	return fData[2];
}