#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	Vertices = nullptr;
	unsigned int VerticesSize = 0;

	indexBuffer = nullptr; //index buffer
	indexBufferSize = 0;


	NumIndices = 0;
	BaseVertex = 0;
	BaseIndex = 0;
	MaterialIndex = 0xFFFFFFFF;

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

<<<<<<< HEAD
void Mesh::Init()
=======
void Mesh::SetMesh()
{

}

void Mesh::Update()
>>>>>>> parent of 89f9bc6 (Parcial 1)
{
}

void Mesh::Render()
{
<<<<<<< HEAD
#if defined (DX11)

	_rManager.UpdateSubresourceDX11(_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);

	// Modify the color
	g_vMeshColor.x = 0.75;
	g_vMeshColor.y = 0.75;
	g_vMeshColor.z = 0.75;

	//modify mesh in world
	g_World = XMMatrixTranslation(position.getX(), position.getY(), position.getZ());
	g_World *= XMMatrixRotationRollPitchYaw(rotation.getX(), rotation.getY(), rotation.getZ());
	g_World *= XMMatrixScaling(scale.getX(), scale.getY(), scale.getZ());
	cb.mWorld = XMMatrixTranspose(g_World);
	//cb.vMeshColor = g_vMeshColor;
#endif
=======
>>>>>>> parent of 89f9bc6 (Parcial 1)
}

void Mesh::MoveMesh()
{
}
<<<<<<< HEAD

#elif defined (OGL)
#endif
=======
>>>>>>> parent of 89f9bc6 (Parcial 1)



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

void Mesh::setVertexLight(VertexLight* newVertex, unsigned int vertexCount)
{
	VerticesSize = vertexCount;
	
	if (nullptr == vertexLight) {
		vertexLight = new VertexLight[VerticesSize];
	}
	/*else {
		delete[] indexBuffer;
		vertexLight = new VertexLight[VerticesSize];
	}*/

	memcpy(vertexLight, newVertex, sizeof(VertexLight) * VerticesSize);
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


	


	
