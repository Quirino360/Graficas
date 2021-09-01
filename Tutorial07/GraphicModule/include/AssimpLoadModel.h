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
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Mesh.h"

#define NUM_BONES_PER_VEREX 4

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

    std::vector<Mesh> m_Entries;
    std::vector<Texture*> m_Textures;

	int numVertex;
	Vertex* vertices;
    VertexLight* vertexLight;

	int numIndices;
	unsigned short* indices; 
	std::vector<unsigned short> indexBuff; 

	std::string filename;

private:
    std::vector<float>  vertexBuff;
    std::vector<const aiNode*> nodeBuff;
    unsigned int numNodeBuff;

    // -------------------- Bones
    aiMatrix4x4 m_GlobalInverseTransform;
    unsigned int numBones;
    std::map<std::string, unsigned int> m_BoneMapping;
    std::vector<BoneInfo> m_BoneInfo;

    bool m_withAdjacencies = false;

#ifdef OGL

    GLuint m_Buffers[VB_TYPES::COUNT];
    GLuint m_VAO;
#endif 
public:
    bool loadModel(std::string file);
    void Render();

private:
	void assimpGetMeshData(aiMesh* _mesh); 
    bool processData();
    void InitMesh(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<Vec3>& Positions, std::vector<Vec3>& Normals, std::vector<Vec2 >& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices);

    // -------------------- Bones
    void LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);
    void BoneTransform(float TimeInSeconds, std::vector<aiMatrix4x4>& Transforms); //update this
    void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform);

    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    aiNodeAnim*  FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);


public:

    Vertex* getVertexData();
    VertexLight* getVertexLightData();
    std::vector<unsigned short>* getIndexData();


private:


};
