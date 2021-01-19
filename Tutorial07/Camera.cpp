#include "Camera.h"
#include "VecMath.h"
Camera::Camera()
{
	eye = new Vector3(0, 0, 0);
	at = new Vector3(0, 0, 0);
	up = new Vector3(0, 0, 0);
}

Camera::Camera(Vector3 _eye, Vector3 _at, Vector3 _up)
{
	eye = new Vector3(_eye);
	at = new Vector3(_at);
	up = new Vector3(_up);
}

Camera::~Camera()
{
	if (eye != nullptr){
		delete eye;
		eye = nullptr;
	}
	if (at != nullptr) {
		delete at;
		up = nullptr;
	}
	if (up != nullptr) {
		delete up;
		up = nullptr;
	}
}

void Camera::setViewMatrix()
{
	Vector3 axisZ = VecMath::normalize3(VecMath::substarct3(*at, *eye));
	Vector3 axisX = VecMath::normalize3(VecMath::crossProduct3(*up, axisZ));
	Vector3 axisY = VecMath::crossProduct3(axisZ, axisX);

	viewMatrix = new Matrix4(	axisX.getX(), axisY.getX(), axisZ.getX(), 0,
								axisX.getY(), axisY.getY(), axisZ.getY(), 0,
								axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
								-VecMath::dotProduct3(axisX,*eye), -VecMath::dotProduct3(axisY,*eye),-VecMath::dotProduct3(axisZ,*eye), 1);
}
void Camera::setViewMatrix(Vector3 _eye, Vector3 _at, Vector3 _up)
{
	Vector3 axisZ = VecMath::normalize3(VecMath::substarct3(_at, _eye));
	Vector3 axisX = VecMath::normalize3(VecMath::crossProduct3(_up, axisZ));
	Vector3 axisY = VecMath::crossProduct3(axisZ, axisX);

	viewMatrix = new Matrix4(axisX.getX(), axisY.getX(), axisZ.getX(), 0,
		axisX.getY(), axisY.getY(), axisZ.getY(), 0,
		axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
		-VecMath::dotProduct3(axisX, _eye), -VecMath::dotProduct3(axisY, _eye), -VecMath::dotProduct3(axisZ, _eye), 1);
}

void Camera::setMatrixPerspective(float _fovAngleY, float _aspectRatio, float _persNearZ, float _persFarZ)
{
	float SinFov, CosFov, Height, Width;

	SinFov = sin(_fovAngleY / 2);
	CosFov = cos(_fovAngleY / 2);

	Height = CosFov / SinFov;
	Width = Height / _aspectRatio;

	Vector4 A = Vector4(Width, 0.0f, 0.0f, 0.0f);
	Vector4 B = Vector4(0.0f, Height, 0.0f, 0.0f);
	Vector4 C = Vector4(0.0f, 0.0f, _persFarZ / (_persFarZ - _persNearZ), 1.0f);
	Vector4 D = Vector4(0.0f, 0.0f, -C.getZ() * _persNearZ, 0.0f);

	matrixPerspective = new Matrix4(A, B, C, D);
}

void Camera::setMatrixOrthographic(float _viewWidth, float _viewHeight, float _orthoNearZ, float _orthoFarZ)
{
	float fRange;

	fRange = 1.0f / (_orthoFarZ - _orthoNearZ);

	Vector4 A = Vector4(2.0f / _viewWidth, 0.0f, 0.0f, 0.0f);
	Vector4 B = Vector4(0.0f, 2.0f / _viewHeight, 0.0f, 0.0f);
	Vector4 C = Vector4(0.0f, 0.0f, fRange, 0.0f);
	Vector4 D = Vector4(0.0f, 0.0f, -fRange * _orthoNearZ, 1.0f);

	matrixOrthographic = new Matrix4(A, B, C, D);
}