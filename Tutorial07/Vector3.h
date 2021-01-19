#pragma once


class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

private:

	float x;
	float y;
	float z;

public:
	//Geters
	float getX() { return x; };
	float getY() { return y; };
	float getZ() { return z; };

	//Seters
	void setX(float _x) { x = _x; };
	void setY(float _y) { y = _y; };
	void setZ(float _z) { z = _z; };

private:
	
};

