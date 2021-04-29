#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	Vertices = nullptr;
	unsigned int VerticesSize = 0;

	indexBuffer = nullptr; //index buffer
	indexBufferSize = 0;
}

Mesh::~Mesh()
{
	if (nullptr != Vertices)
	{
		delete[] Vertices;
		Vertices = nullptr;
	}
	if (nullptr != indexBuffer)
	{
		delete[] indexBuffer;
		indexBuffer = nullptr;
	}
}

void Mesh::SetMesh()
{

}

void Mesh::Update()
{
}

void Mesh::Render()
{
}

void Mesh::MoveMesh()
{
}

void Mesh::setVetices(Vertex* newVertex, unsigned int vertexCount)
{
	VerticesSize = vertexCount;

	if (nullptr == Vertices) {
		Vertices = new Vertex[VerticesSize];
	}
	/*else {
		delete[] indexBuffer;
		Vertices = new Vertex[VerticesSize];
	}*/
	
	memcpy(Vertices, newVertex, sizeof(Vertex) * VerticesSize);
}

void Mesh::setIndexBuffer(unsigned short* newIndexBuffer, unsigned int newIndexBufferSize)
{
	indexBufferSize = newIndexBufferSize;

	if (nullptr == indexBuffer) {
		indexBuffer = new unsigned short[indexBufferSize];
	}
	/*else {
		delete[] indexBuffer;
		indexBuffer = new unsigned short[indexBufferSize];
	}*/

	memcpy(indexBuffer, newIndexBuffer, sizeof(unsigned short) * indexBufferSize);
}


	


	
