#pragma once
#include <string>
#include <vector>
#include "Matrix4.h"
#include "Vector3.h"
#include "Material.h"

<<<<<<< HEAD
#include "RenderManager.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Buffer.h"
#include "Buffers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

=======
>>>>>>> parent of 89f9bc6 (Parcial 1)
#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

#elif defined(OGL)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

struct Vec3
{
	Vec3() = default;
	Vec3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; };
	float x, y, z;
};

struct Vec2
{
	Vec2() = default;
	Vec2(float _x, float _y) { x = _x, y = _y; };
	float x, y;
};

<<<<<<< HEAD

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

enum VB_TYPES 
{
	INDEX_BUFFER = 0,
	POS_VB,
	NORMAL_VB,
	TEXCOORD_VB,
	BONE_VB,
	COUNT
};

// vertex buffer // ESTE ES EL INPUT DEL BUFFER
=======
// vertex buffer
>>>>>>> parent of 89f9bc6 (Parcial 1)
struct Vertex
{
#if defined (DX11)
	Vec3 vertex;  // vertex
	Vec2 uvs;  //texture uvs 
	Vec3 normals; //normales
#elif defined (OGL)
	Vec3 vertex;
	Vec2 TexCoords;
	//Vec3 Bones;
#endif
};

<<<<<<< HEAD
struct BoneInfo
{
	aiMatrix4x4 BoneOffset;
	aiMatrix4x4 FinalTransformation;
};

struct VertexBoneData
{
	unsigned int* IDs;
	float* Weights;
	void AddBoneData(unsigned int BoneID, float Weight)
	{
		for (int i = 0; i < sizeof(IDs) / sizeof(*IDs); i++) {
			if (Weights[i] == 0.0) {
				IDs[i] = BoneID;
				Weights[i] = Weight;
				return;
			}
		}

		// should never get here - more bones than we have space for
		//assert(0);
	};
};

struct VertexLight
{
	Vec3 position;
	Vec2 texCoord;
};
=======

>>>>>>> parent of 89f9bc6 (Parcial 1)

class Mesh
{
public:
	Mesh();
	~Mesh();

<<<<<<< HEAD
#if defined(DX11)
	CBChangesEveryFrame cb;

	XMMATRIX                            g_World;
	XMFLOAT4                            g_vMeshColor;

	Vector3                            position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3                            rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3                            scale = Vector3(1.0f, 1.0f, 1.0f);
#endif


	unsigned int NumIndices;
	unsigned int BaseVertex;
	unsigned int BaseIndex;
	unsigned int MaterialIndex;


private:
=======
private:

	//Matrix4* worldMatrix;

>>>>>>> parent of 89f9bc6 (Parcial 1)
	Vertex* Vertices;
	VertexLight* vertexLight;
	unsigned int VerticesSize;


	unsigned short* indexBuffer; //index buffer
	unsigned int indexBufferSize;

	std::string fileName;

public:
<<<<<<< HEAD
	
	void Init();
	// -------------------- Bones 

#if defined (DX11)
	void Update(RenderManager& _rManager, Buffer*& _pCBChangesEveryFrame);
	void Render(RenderManager& _rManager, RenderTargetView*& _targetView, ID3D11ShaderResourceView*& _resourceView, DepthStencilView*& _dStencilView,unsigned int _textureSlot);
#elif defined (OGL)

#endif
=======

	void SetMesh();
	void Update();
	void Render();
	void MoveMesh();

>>>>>>> parent of 89f9bc6 (Parcial 1)

	//------------------ getters ---------------------//
	Vertex* getVertices() { return Vertices; };
	VertexLight* getVertexLight() { return vertexLight; }
	unsigned int getVerticesSize() { return VerticesSize; };

	unsigned short* getIndexBuffer() { return indexBuffer; }
	unsigned int getIndexBufferSize() { return indexBufferSize; };

	//------------------ =setters ---------------------//
<<<<<<< HEAD
=======


>>>>>>> parent of 89f9bc6 (Parcial 1)
	void setVetices(Vertex* newVertex, unsigned int vertexCount);
	void setVertexLight(VertexLight* newVertex, unsigned int vertexCount);
	void setIndexBuffer(unsigned short* newIndexBuffer, unsigned int newIndexBufferSize);

	void SetFileName(std::string _fileName) { fileName = _fileName; };
	std::string getFileName() { return fileName; };


private:




};

