#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#elif defined(OGL)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Mesh.h"

//class aiMesh;

class AssimpLoadModel
{
public:

    AssimpLoadModel();
    ~AssimpLoadModel();

    Assimp::Importer importer;
    const aiScene* modelScene;
    const aiNode* modelNode;
    const aiMesh* modelMesh;
    const aiFace* modelFace;


	int numVertex;
	Vertex* vertices;


	int numIndices;
	unsigned short* indices; 
	std::vector<unsigned short> indexBuff; 



	std::string filename;

private:
    std::vector<float>  vertexBuff;
    std::vector<const aiNode*> nodeBuff;
    unsigned int numNodeBuff;

public:
	void assimpGetMeshData(aiMesh* _mesh); 

    bool loadModel(std::string file);
    bool processData();
    Vertex* getVertexData();
    std::vector<unsigned short>* getIndexData();

private:


};
