#include "Camera.h"
#include "VecMath.h"
Camera::Camera()
{
	fFrame = true;

	//------- Up, Right, Front ----------- //
	axisX = Vector3(0, 0, 0); // Right
	axisY = Vector3(0, 0, 0); // Front 
	axisZ = Vector3(0, 0, 0); // Up

	// ------------- View Matrix -------------- //
	viewMatrix = nullptr;
	eye = new Vector3(0, 0, 0);
	at = new Vector3(0, 0, 0);
	up = new Vector3(0, 0, 0);
	position = nullptr;

	// ------------ Matrix Perspective -------------- // 
	matrixPerspective = nullptr;
	fovAngleY = new float(0);
	aspectRatio = new float(0);
	persNearZ = new float(0);
	persFarZ = new float(0);

	// ------------ Matrix Orthographic --------------- //
	matrixOrthographic;
	viewWidth = nullptr;
	viewHeight = nullptr;
	orthoNearZ = nullptr;
	orthoFarZ = nullptr;
}

Camera::Camera(Vector3 _eye, Vector3 _at, Vector3 _up)
{
	fFrame = true;

	//------- Up, Right, Front ----------- //
	axisX = Vector3(0, 0, 0); // Right
	axisY = Vector3(0, 0, 0); // Front
	axisZ = Vector3(0, 0, 0); // Up

	// ------------- View Matrix -------------- //
	viewMatrix = nullptr;
	eye = new Vector3(_eye);
	at = new Vector3(_at);
	up = new Vector3(_up);
	position = nullptr;

	// ------------ Matrix Perspective -------------- // 
	matrixPerspective = nullptr;
	fovAngleY = new float(0);
	aspectRatio = new float(0);
	persNearZ = new float(0);
	persFarZ = new float(0);

	// ------------ Matrix Orthographic --------------- //
	matrixOrthographic;
	viewWidth = nullptr;
	viewHeight = nullptr;
	orthoNearZ = nullptr;
	orthoFarZ = nullptr;


}

Camera::~Camera()
{
	// ------------- View Matrix -------------- //
	if (nullptr != viewMatrix)
	{
		delete viewMatrix;
		viewMatrix = nullptr;
	}
	if (nullptr != eye)
	{
		delete eye;
		eye = nullptr;
	}
	if (nullptr != at)
	{
		delete at;
		at = nullptr;
	}
	if (nullptr != up)
	{
		delete up;
		up = nullptr;
	}
	if (nullptr != position)
	{
		delete position;
		position = nullptr;
	}


	// ------------ Matrix Perspective -------------- // 
	if (nullptr != matrixPerspective)
	{
		delete matrixPerspective;
		matrixPerspective = nullptr;
	}
	if (nullptr != fovAngleY)
	{
		delete fovAngleY;
		fovAngleY = nullptr;
	}
	if (nullptr != aspectRatio)
	{
		delete aspectRatio;
		aspectRatio = nullptr;
	}
	if (nullptr != persNearZ)
	{
		delete persNearZ;
		persNearZ = nullptr;
	}
	if (nullptr != persFarZ)
	{
		delete persFarZ;
		persFarZ = nullptr;
	}

	// ------------ Matrix Orthographic --------------- //
	if (nullptr != matrixOrthographic)
	{
		delete matrixOrthographic;
		matrixOrthographic = nullptr;
	}
	if (nullptr != viewWidth)
	{
		delete viewWidth;
		viewWidth = nullptr;
	}
	if (nullptr != viewHeight)
	{
		delete viewHeight;
		viewHeight = nullptr;
	}
	if (nullptr != orthoNearZ)
	{
		delete orthoNearZ;
		orthoNearZ = nullptr;
	}
	if (nullptr != orthoFarZ)
	{
		delete orthoFarZ;
		orthoFarZ = nullptr;
	}
}

void Camera::RotateCamera(Vector3 lpnew, Vector3 lpold)
{
	if (!fFrame)// skip first frame
	{
		Vector3 newAt = VecMath::substarct3(lpnew, lpold);
		newAt = VecMath::divide3(newAt, 100);

		setAt(VecMath::add3(*at, newAt));

		setViewMatrix();
	}
	fFrame = false;
}

void Camera::move(float x, float y, float z)
{
	Vector3 A = VecMath::multiply3(x, axisX);
	Vector3 B = VecMath::multiply3(y, axisY);
	Vector3 C = VecMath::multiply3(z, axisZ);

	*eye = VecMath::add3(A, *eye);
	*eye = VecMath::add3(B, *eye);
	*eye = VecMath::add3(C, *eye);
	
	*at = VecMath::add3(A, *at);
	*at = VecMath::add3(B, *at);
	*at = VecMath::add3(C, *at);

	setViewMatrix();
	//setMatrixPerspective(*persFarZ, *aspectRatio, *persNearZ, *persFarZ);
}

void Camera::update()
{
	//setViewMatrix();
	//setMatrixPerspective();
	//setMatrixOrthographic();
}

void Camera::setViewMatrix()
{
	axisZ = VecMath::normalize3(VecMath::substarct3(*at, *eye));
	axisX = VecMath::normalize3(VecMath::crossProduct3(*up, axisZ));
	axisY = VecMath::crossProduct3(axisZ, axisX);

	if (nullptr == viewMatrix)
	{
		viewMatrix = new Matrix4(axisX.getX(), axisY.getX(), axisZ.getX(), 0,
			axisX.getY(), axisY.getY(), axisZ.getY(), 0,
			axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
			-VecMath::dotProduct3(axisX, *eye), -VecMath::dotProduct3(axisY, *eye), -VecMath::dotProduct3(axisZ, *eye), 1);
	}
	else
	{
		*viewMatrix = Matrix4(axisX.getX(), axisY.getX(), axisZ.getX(), 0,
			axisX.getY(), axisY.getY(), axisZ.getY(), 0,
			axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
			-VecMath::dotProduct3(axisX, *eye), -VecMath::dotProduct3(axisY, *eye), -VecMath::dotProduct3(axisZ, *eye), 1);
	}

}
void Camera::setViewMatrix(Vector3 _eye, Vector3 _at, Vector3 _up)
{
	axisZ = VecMath::normalize3(VecMath::substarct3(_at, _eye));
	axisX = VecMath::normalize3(VecMath::crossProduct3(_up, axisZ));
	axisY = VecMath::crossProduct3(axisZ, axisX);

	if (nullptr == viewMatrix) {
		viewMatrix = new Matrix4(axisX.getX(), axisY.getX(), axisZ.getX(), 0,
			axisX.getY(), axisY.getY(), axisZ.getY(), 0,
			axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
			-VecMath::dotProduct3(axisX, _eye), -VecMath::dotProduct3(axisY, _eye), -VecMath::dotProduct3(axisZ, _eye), 1);
	}
	else {
		*viewMatrix =  Matrix4(axisX.getX(), axisY.getX(), axisZ.getX(), 0,
			axisX.getY(), axisY.getY(), axisZ.getY(), 0,
			axisX.getZ(), axisY.getZ(), axisZ.getZ(), 0,
			-VecMath::dotProduct3(axisX, _eye), -VecMath::dotProduct3(axisY, _eye), -VecMath::dotProduct3(axisZ, _eye), 1);
	}

}

void Camera::setMatrixPerspective(float _fovAngleY, float _aspectRatio, float _persNearZ, float _persFarZ)
{
	 *fovAngleY = _fovAngleY;
	 *aspectRatio = _aspectRatio;
	 *persNearZ = _persNearZ;
	 *persFarZ = _persFarZ;

	float SinFov, CosFov, Height, Width;

	SinFov = sin(_fovAngleY / 2);
	CosFov = cos(_fovAngleY / 2);

	Height = CosFov / SinFov;
	Width = Height / _aspectRatio;

	Vector4 A = Vector4(Width, 0.0f, 0.0f, 0.0f);
	Vector4 B = Vector4(0.0f, Height, 0.0f, 0.0f);
	Vector4 C = Vector4(0.0f, 0.0f, _persFarZ / (_persFarZ - _persNearZ), 1.0f);
	Vector4 D = Vector4(0.0f, 0.0f, -C.getZ() * _persNearZ, 0.0f);

	if (nullptr == matrixPerspective)
		matrixPerspective = new Matrix4(A, B, C, D);
	else
		*matrixPerspective = Matrix4(A, B, C, D);
}

void Camera::setMatrixOrthographic(float _viewWidth, float _viewHeight, float _orthoNearZ, float _orthoFarZ)
{
	float fRange;

	fRange = 1.0f / (_orthoFarZ - _orthoNearZ);

	Vector4 A = Vector4(2.0f / _viewWidth, 0.0f, 0.0f, 0.0f);
	Vector4 B = Vector4(0.0f, 2.0f / _viewHeight, 0.0f, 0.0f);
	Vector4 C = Vector4(0.0f, 0.0f, fRange, 0.0f);
	Vector4 D = Vector4(0.0f, 0.0f, -fRange * _orthoNearZ, 1.0f);

	if (nullptr == matrixOrthographic)
		matrixOrthographic = new Matrix4(A, B, C, D);
	else
		*matrixOrthographic = Matrix4(A, B, C, D);
}
