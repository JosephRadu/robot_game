#ifndef __V3D_H
#define __V3D_H

class V3D
{
private:
	float fData[3];
public:
	V3D();
	V3D(float allValues);
	V3D(float x, float y, float z);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void set(float x, float y, float z);
	void set(V3D vector);

	// Returns x componenet of vector.
	float x() const;
	// Returns y componenet of vector.
	float y() const;
	// Returns z componenet of vector.
	float z() const;
};


#endif