#pragma once
class Vector4
{
public:
	Vector4();
	Vector4(float _x, float _y, float _z, float _w);
	~Vector4();

private:

	float x;
	float y;
	float z;
	float w;

public:
	//Geters
	float getX() { return x; };
	float getY() { return y; };
	float getZ() { return z; };
	float getW() { return w; };

	//Seters
	void setX(float _x) { x = _x; };
	void setY(float _y) { y = _y; };
	void setZ(float _z) { z = _z; };
	void setW(float _w) { w = _w; };
private:
};

