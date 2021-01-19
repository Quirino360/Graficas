#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4.h"


class Camera
{
public:
	Camera();
	Camera(Vector3 _eye, Vector3 _at, Vector3 _up);
	~Camera();

private:
	// ------------- View Matrix -------------- //
	Matrix4* viewMatrix;
	Vector3* eye;
	Vector3* at;
	Vector3* up;
	Vector3* position;

	// ------------ Matrix Perspective -------------- // 
	Matrix4* matrixPerspective;
	float* fovAngleY;
	float* aspectRatio;
	float* persNearZ;
	float* persFarZ;

	// ------------ Matrix Orthographic --------------- //
	Matrix4* matrixOrthographic;
	float* viewWidth;
	float* viewHeight;
	float* orthoNearZ;
	float* orthoFarZ;

public:
	// ------------- View Matrix -------------- //

	//Getters
	Matrix4 getViewMatrix() { return *viewMatrix; };
	Vector3 getEye() { return *eye; };
	Vector3 getAt() { return *at; };
	Vector3 getUp() { return *up; };
	Vector3 getPosition() { return *position; };

	//Setters
	void setViewMatrix();
	void setViewMatrix(Vector3 _eye, Vector3 _at, Vector3 _up);

	void setEye(Vector3 newVec) { eye = new Vector3(newVec); };
	void setEye(float _x, float _y, float _z) { eye = new Vector3(_x, _y, _z); };
	void setAt(Vector3 newVec) { at = new Vector3(newVec); };
	void setAt(float _x, float _y, float _z) { at = new Vector3(_x, _y, _z); };
	void setUp(Vector3 newVec) { up = new Vector3(newVec); };
	void setUp(float _x, float _y, float _z) { up = new Vector3(_x, _y, _z); };
	void setPosition(Vector3 newVec) { position = new Vector3(newVec); };
	void setPosition(float _x, float _y, float _z) { position = new Vector3(_x, _y, _z); };


	// ------------ Matrix Perspective -------------- // 

	//Getters
	Matrix4 getMatrixPerspective() { return *matrixPerspective; };
	float getFovAngleY() { return *fovAngleY; };
	float getAspectRatio() { return *aspectRatio; };
	float getPersNearZ() { return *persNearZ; };
	float getPersFarZ() { return *persNearZ; };

	//Setters
	void setMatrixPerspective(Matrix4 _matrixPerspective) { matrixPerspective = new Matrix4(_matrixPerspective); };
	void setMatrixPerspective(float _fovAngleY, float _aspectRatio, float _persNearZ, float _persFarZ);

	void setFovAngleY(float _fovAngleY) { fovAngleY = new float(_fovAngleY); };
	void setAspectRatio(float _aspectRatio) { aspectRatio = new float(_aspectRatio); };
	void setPersNearZ(float _persNearZ) { persNearZ = new float(_persNearZ); };
	void setPersFarZ(float _persFarZ) { persFarZ = new float(_persFarZ); };

	// ------------ Matrix Orthographic --------------- //

	//Getters
	Matrix4 getMatrixOrthographic() { return *matrixOrthographic; };
	float getViewWidth() { return *viewWidth; };
	float getViewHeight() { return *viewHeight; };
	float getOrthoNearZ() { return *orthoNearZ; };
	float getOrthoFarZ() { return *orthoFarZ; };

	//Setters 
	void setMatrixOrthographic(Matrix4 _matrixOrthographic) { matrixOrthographic = new Matrix4(_matrixOrthographic); };
	void setMatrixOrthographic(float _viewWidth, float _viewHeight, float _orthoNearZ, float _orthoFarZ);

	void setViewWidth(float _viewWidth) { viewWidth = new float(_viewWidth); };
	void setViewHeight(float _viewHeight) { viewHeight = new float(_viewHeight); };
	void setOrthoNearZ(float _orthoNearZ) { orthoNearZ = new float(_orthoNearZ); };
	void setOrthoFarZ(float _orthoFarZ) { orthoFarZ = new float(_orthoFarZ); };

private:
	
};

