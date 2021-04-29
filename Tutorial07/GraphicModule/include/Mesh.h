#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <string>
#include "Material.h"

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#elif defined(OGL)
#endif


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
#if defined (DX11)
	Vec3 vertex;  // vertex
	Vec2 uvs;  //texture uvs 
	Vec3 normals; //normales
#elif defined (OGL)
	Vec3 vertex;
	Vec2 TexCoords;
#endif
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

	std::string fileName;

public:

	void SetMesh();
	void Update();
	void Render();
	void MoveMesh();


	//------------------ getters ---------------------//


	Vertex* getVertices() { return Vertices; };
	unsigned int getVerticesSize() { return VerticesSize; };

	unsigned short* getIndexBuffer() { return indexBuffer; }
	unsigned int getIndexBufferSize() { return indexBufferSize; };

	//------------------ =setters ---------------------//


	void setVetices(Vertex* newVertex, unsigned int vertexCount);
	void setIndexBuffer(unsigned short* newIndexBuffer, unsigned int newIndexBufferSize);

	void SetFileName(std::string _fileName) { fileName = _fileName; };
	std::string getFileName() { return fileName; };


private:




};

