#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <string>
#include "Material.h"

#include "Structs.h"
#include "RenderManager.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Buffer.h"

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

// vertex buffer // ESTE ES EL INPUT DEL BUFFER
struct Vertex
{
#if defined (DX11)
	Vec3 vertex;  // vertex
	Vec3 normals; //normales
	Vec2 uvs;  //texture uvs 
	Vec3 binormal;
	Vec3 tangent;

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

#if defined(DX11)
	GraphicsModule::CBChangesEveryFrame cb;

	XMMATRIX                            g_World;
	XMFLOAT4                            g_vMeshColor;

	Vector3                            position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3                            rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3                            scale = Vector3(1.0f, 1.0f, 1.0f);
#endif

private:

	Vertex* Vertices;
	unsigned int VerticesSize;

	unsigned short* indexBuffer; //index buffer
	unsigned int indexBufferSize;

	std::string fileName;

public:
	
	void SetMesh();
	void Init();
#if defined (DX11)
	void Update(RenderManager& _rManager, Buffer*& _pCBChangesEveryFrame);
	void Render(RenderManager& _rManager, RenderTargetView*& _targetView, ID3D11ShaderResourceView*& _resourceView, DepthStencilView*& _dStencilView,unsigned int _textureSlot);
#endif

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

