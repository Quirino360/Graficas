#pragma once
#include "Matrix4.h"
#include "Vector3.h"



struct Vec3
{
	float x, y, z;
};

struct Vec2
{
	float x, y;
};

// vertex buffer
struct Vertex
{
	 Vec3 vertex;  // vertex
	 Vec2 uvs;  //texture uvs 
};



class Mesh
{
public:
	Mesh();
	~Mesh();

private:

	//Matrix4* worldMatrix;

	Vertex* Vertices;
	unsigned int VerticesSize;

	unsigned short* indexBuffer; //index buffer
	unsigned int indexBufferSize;

public:

	//------------------ getters ---------------------//
	Vertex* getVertices() { return Vertices; };
	unsigned int getVerticesSize() { return VerticesSize; };

	unsigned short* getIndexBuffer() { return indexBuffer; }
	unsigned int getIndexBufferSize() { return indexBufferSize; };

	//------------------ =setters ---------------------//
	void setVetices(Vertex* newVertex, unsigned int vertexCount);
	void setIndexBuffer(unsigned short* newIndexBuffer, unsigned int newIndexBufferSize);




private:




};

