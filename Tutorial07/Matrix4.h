#pragma once
#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
public:
	Matrix4();
	Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
	Matrix4(Vector4 A, Vector4 B, Vector4 C, Vector4 D);
	~Matrix4();

	float* matrix4;

private:


public:
	float* getMatrix4() { return matrix4; };
	
	void setMatrix4(float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33);


private:

};

