#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::setVetices(Vertex* newVertex, unsigned int vertexCount)
{
	VerticesSize = vertexCount;

	Vertices = new Vertex[VerticesSize];
	
	memcpy(Vertices, newVertex, sizeof(Vertex) * VerticesSize);

}

void Mesh::setIndexBuffer(unsigned short* newIndexBuffer, unsigned int newIndexBufferSize)
{
	indexBufferSize = newIndexBufferSize;

	indexBuffer = new unsigned short[indexBufferSize];

	memcpy(indexBuffer, newIndexBuffer, sizeof(unsigned short) * indexBufferSize);

}


	


	
