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

	bool fFrame;
	//------- Up, Right, Front ----------- //
	Vector3 axisX; // Right
	Vector3 axisY; // Front
	Vector3 axisZ; // Up


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

	/**
	 * @brief   Rotates the camera with the mouse position 
	 * @param   #Vector3 new cursor position
	 * @param   #Vector3 old cursor position
	 * @bug     NA
	 * @return  #void
	 */
	void RotateCamera(Vector3 lpnew, Vector3 lpold);

	/**
	 * @brief   moves the camera position
	 * @param   #float move camera in axis x
	 * @param   #float move camera in axis y
	 * @param   #float move camera in axis z
	 * @bug     NA
	 * @return  #void
	 */
	void move(float x, float y, float z);

	/** 
	 * @brief	what it need to be updated in the camera 
	 * @bug     doesn't works right now
	 * @return  #void 
	 */
	void update();

	// ------------- View Matrix -------------- //
	//Getters

	Matrix4 getViewMatrix() { return *viewMatrix; };		// @returns #Matrix4 a copy of the viewMatrix
	Vector3 getEye() { return *eye; };					// @returns #Vector3 the eye vector of the viewMatrix
	Vector3 getAt() { return *at; };					// @returns #Vector3 the at vector of the viewMatrix
	Vector3 getUp() { return *up; };					// @returns #Vector3 the up vector of the viewMatrix
	//Vector3 getPosition() { return *position; };		// @returns #Vector3 the position vector of the viewMatrix

	//Setters

	/**
	 * @brief	after setting viewMatrix or viewMatrix primitives this sets the view matrix with the new values
	 * @param   #Vector3 new eye vector
	 * @param	#Vector3 new at vector
	 * @param	#Vector3 new up vector
	 * @bug     NA
	 * @return  #void
	 */
	void setViewMatrix();											
	void setViewMatrix(Vector3 _eye, Vector3 _at, Vector3 _up);	

	void setEye(Vector3 newVec) { *eye = newVec; };									// sets the Vector3 eye pointer value, with the Vector3 given parameter
	void setEye(float _x, float _y, float _z) { *eye = Vector3(_x, _y, _z); };		// sets the Vector3 eye pointer value, with the new float values in x, y & z 

	void setAt(Vector3 newVec) { *at = newVec; };									// sets the Vector3 at pointer value, with the Vector3 given parameter
	void setAt(float _x, float _y, float _z) { *at = Vector3(_x, _y, _z); };		// sets the Vector3 at pointer value, with the new float values in x, y & z 

	void setUp(Vector3 newVec) { *up = newVec; };									//sets the Vector3 up pointer value, with the Vector3 given parameter
	void setUp(float _x, float _y, float _z) { *up = Vector3(_x, _y, _z); };		// sets the Vector3 up pointer value, with the new float values in x, y & z 

	void setPosition(Vector3 newVec) { *position = newVec; };								// sets the Vector3 position pointer value, with the Vector3 given parameter
	void setPosition(float _x, float _y, float _z) { *position = Vector3(_x, _y, _z); };	// sets the Vector3 position pointer value, with the new float values in x, y & z 


	// ------------ Matrix Perspective -------------- // 
	//Getters

	Matrix4 getMatrixPerspective() { return *matrixPerspective; };	// @returns #Matrix4 a copy of the viewMatrix value
	float getFovAngleY() { return *fovAngleY; };					// @returns #float a copy of the fovAngleY pointer value
	float getAspectRatio() { return *aspectRatio; };				// @returns #float a copy of the aspectRatio pointer value
	float getPersNearZ() { return *persNearZ; };					// @returns #float a copy of the persNearZ pointer value
	float getPersFarZ() { return *persFarZ; };						// @returns #float a copy of the persFarZ pointer value

	//Setters

	void setMatrixPerspective(Matrix4 _matrixPerspective) { *matrixPerspective = _matrixPerspective; };		// sets the Matrix4 matrixPerspective pointer value, with the Matrix4 given parameter
	void setMatrixPerspective(float _fovAngleY, float _aspectRatio, float _persNearZ, float _persFarZ);		// sets the Matrix4 matrixPerspective pointer value, with the new float values of: _fovAngleY, _aspectRatio, _persNearZ, _persFarZ

	void setFovAngleY(float _fovAngleY) { *fovAngleY = _fovAngleY; };			// sets the float fovAngleY pointer value, with the float given parameter
	void setAspectRatio(float _aspectRatio) { *aspectRatio = _aspectRatio; };	// sets the float aspectRatio pointer value, with the float given parameter
	void setPersNearZ(float _persNearZ) { *persNearZ = _persNearZ; };			// sets the float persNearZ pointer value, with the float given parameter
	void setPersFarZ(float _persFarZ) { *persFarZ =_persFarZ; };				// sets the float persFarZ pointer value, with the float given parameter


	// ------------ Matrix Orthographic --------------- //
	//Getters

	Matrix4 getMatrixOrthographic() { return *matrixOrthographic; };	// @returns #Matrix4 a copy of the viewMatrix value
	float getViewWidth() { return *viewWidth; };			// @returns #float a copy of the fovAngleY pointer value
	float getViewHeight() { return *viewHeight; };			// @returns #float a copy of the fovAngleY pointer value
	float getOrthoNearZ() { return *orthoNearZ; };			// @returns #float a copy of the fovAngleY pointer value
	float getOrthoFarZ() { return *orthoFarZ; };			// @returns #float a copy of the fovAngleY pointer value


	//Setters 

	void setMatrixOrthographic(Matrix4 _matrixOrthographic) { *matrixOrthographic = Matrix4(_matrixOrthographic); };		// sets the Matrix4 _matrixOrthographic pointer value, with the Matrix4 given parameter
	void setMatrixOrthographic(float _viewWidth, float _viewHeight, float _orthoNearZ, float _orthoFarZ);					// sets the Matrix4 matrixPerspective pointer value, with the new float values of: _viewWidth, _viewHeight, _orthoNearZ, _orthoFarZ

	void setViewWidth(float _viewWidth) { *viewWidth = _viewWidth; };			// sets the float viewWidth pointer value, with the float given parameter
	void setViewHeight(float _viewHeight) { *viewHeight = _viewHeight; };		// sets the float viewHeight pointer value, with the float given parameter
	void setOrthoNearZ(float _orthoNearZ) { *orthoNearZ = _orthoNearZ; };		// sets the float orthoNearZ pointer value, with the float given parameter
	void setOrthoFarZ(float _orthoFarZ) { *orthoFarZ = _orthoFarZ; };			// sets the float orthoFarZ pointer value, with the float given parameter

private:

};

