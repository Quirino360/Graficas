#pragma once

#include <math.h>

#include "Vector4.h"
#include "Vector3.h"


namespace VecMath
{

	//add vectors
	Vector3 add3(Vector3 A, Vector3 B){
		return Vector3(A.getX() + B.getX(), A.getY() + B.getY(), A.getZ() + B.getZ());
	}
	Vector4 add4(Vector4 A, Vector4 B){
		return Vector4(A.getX() + B.getX(), A.getY() + B.getY(), A.getZ() + B.getZ(), A.getW() + B.getW());
	}

	//substarct vectors
	Vector3 substarct3(Vector3 A, Vector3 B) {
		return  Vector3(A.getX() - B.getX(), A.getY() - B.getY(), A.getZ() - B.getZ());
	}
	Vector4 substarct4(Vector4 A, Vector4 B) {
		return Vector4(A.getX() - B.getX(), A.getY() - B.getY(), A.getZ() - B.getZ(), A.getW() - B.getW());
	}

	//multiply vectors
	Vector3 multiply3(float x, Vector3 A){
		return Vector3(x * A.getX(), x * A.getY(), x * A.getZ());
	}
	Vector4 multiply4(float x, Vector4 A){
		return Vector4(x * A.getX(), x * A.getY(), x * A.getZ(), x*A.getW());
	}

	//magnitude of a vector
	float magnitud3(Vector3 A) {
		return float(sqrt((A.getX(), 2) + pow(A.getY(), 2) + pow(A.getZ(), 2)));
	}
	float magnitud4(Vector4 A) {
		return float(sqrt( (A.getX(), 2) + pow(A.getY(), 2) + pow(A.getZ(), 2) + pow(A.getW(), 2) ));
	}


	//normalize a vector
	Vector3 normalize3(Vector3 A){
		float mg = magnitud3(A);
		return Vector3(A.getX() / mg, A.getY() / mg, A.getZ() / mg);
	}
	Vector4 normalize4(Vector4 A){
		float mg = magnitud4(A);
		return Vector4(A.getX() / mg, A.getY() / mg, A.getZ() / mg, A.getW() / mg);
	}

	//dot product of the vectors
	float dotProduct3(Vector3 A, Vector3 B){
		return float((A.getX() * B.getX()) + (A.getY() * B.getY()) + (A.getZ() * B.getZ()));
	}
	float dotProduct4(Vector4 A, Vector4 B) {
		return float((A.getX() * B.getX()) + (A.getY() * B.getY()) + (A.getZ() * B.getZ())+ (A.getW() * B.getW()));
	}
	
	//cross product of the vectors
	Vector3 crossProduct3(Vector3 A, Vector3 B) {
		float i = (A.getY() * B.getZ()) - (A.getZ() * B.getY());
		float j = (A.getX() * B.getZ()) - (A.getZ() * B.getX());
		float k = (A.getX() * B.getY()) - (A.getY() * B.getX());
		return Vector3(i, - j , k);
	}
	Vector4 crossProduct4(Vector4 A, Vector3 B) {
		float i;
		float j;
		float k;
		float l;
		return Vector4();
	}

}
