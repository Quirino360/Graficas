#include "Matrix4.h"

Matrix4::Matrix4():
	Matrix4(0,0,0,0,	0,0,0,0,	0,0,0,0,	0,0,0,0)
{
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	matrix4 = new float[4 * 4] {m00, m01, m02, m03,
								m10, m11, m12, m13,
								m20, m21, m22, m23,
								m30, m31, m32, m33 };
}

Matrix4::Matrix4(Vector4 A, Vector4 B, Vector4 C, Vector4 D)
{
	matrix4 = new float[4 * 4]{ A.getX(), A.getY(), A.getZ(), A.getW(),
								B.getX(), B.getY(), B.getZ(), B.getW(),
								C.getX(), C.getY(), C.getZ(), C.getW(),
								D.getX(), D.getY(), D.getZ(), D.getW() };
}

Matrix4::~Matrix4()
{
	/*if (nullptr != matrix4){
		delete[] matrix4;
		matrix4 = nullptr;
	}*/
}

void Matrix4::setMatrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	delete[] matrix4;

	matrix4 = new float[4 * 4]{ m00, m01, m02, m03,
								m10, m11, m12, m13,
								m20, m21, m22, m23,
								m30, m31, m32, m33 };
}
