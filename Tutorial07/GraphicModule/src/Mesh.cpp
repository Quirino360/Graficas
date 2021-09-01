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

void Mesh::Init()
{
#if defined (DX11)
	g_World = XMMatrixIdentity();
#endif
}

#if defined (DX11)

void Mesh::Update(RenderManager& _rManager, Buffer*& _pCBChangesEveryFrame)
{
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
}

void Mesh::Render(RenderManager& _rManager, RenderTargetView*& _targetView, ID3D11ShaderResourceView*& _resourceView, DepthStencilView*& _dStencilView, unsigned int _textureSlot )
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// ----------------------------------------------- Print an object ---------------------------------------------------------//
	_rManager.ClearRenderTargetViewDX11(_targetView->getRenderTargetViewDX11(), ClearColor);
	_rManager.ClearDepthStencilViewDX11(_dStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	//_rManager.OMSetRenderTargetsDX11(1, &_targetView->getRenderTargetViewDX11(), _dStencilView->getyDepthStencilViewDX11());
	_rManager.PSSetShaderResourcesDX11(_textureSlot, 1, &_resourceView);


}

#elif defined (OGL)
#endif



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


	


	
