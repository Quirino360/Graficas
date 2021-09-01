#include "AssimpLoadModel.h"

AssimpLoadModel::AssimpLoadModel()
{
}

AssimpLoadModel::~AssimpLoadModel()
{
}



void AssimpLoadModel::assimpGetMeshData(aiMesh* _aiMesh)
{
    aiFace* face;
    modelMesh = _aiMesh;

    numVertex = _aiMesh->mNumVertices;
    numIndices = _aiMesh->mNumFaces;

    vertices = new Vertex[numVertex];
    vertexLight = new VertexLight[numVertex];
    indices = new unsigned short[numIndices];

#if defined(DX11)
        for (int j = 0; j < numVertex; j++)
        {
            //Vertex
            vertices[j].vertex.x = _aiMesh->mVertices[j].x;
            vertices[j].vertex.y = _aiMesh->mVertices[j].y;
            vertices[j].vertex.z = _aiMesh->mVertices[j].z;

            vertexLight[j].position.x = _aiMesh->mVertices[j].x;
            vertexLight[j].position.y = _aiMesh->mVertices[j].y;
            vertexLight[j].position.z = _aiMesh->mVertices[j].z;

            //Normales
            vertices[j].normals.x = _aiMesh->mNormals->x;
            vertices[j].normals.y = _aiMesh->mNormals->y;
            vertices[j].normals.z = _aiMesh->mNormals->z;


            //uv
            if (_aiMesh->HasTextureCoords(0)) 
            {
                vertices[j].uvs.x = _aiMesh->mTextureCoords[0][j].x;
                vertices[j].uvs.y = _aiMesh->mTextureCoords[0][j].y;

                vertexLight[j].texCoord.x = _aiMesh->mTextureCoords[0][j].x;
                vertexLight[j].texCoord.y = _aiMesh->mTextureCoords[0][j].y;
            }
            else
            {
                vertices[j].uvs.x = 0;
                vertices[j].uvs.y = 0;

                vertexLight[j].texCoord.x = 0;
                vertexLight[j].texCoord.y = 0;
            }

            vertices[j].tangent.x = _aiMesh->mTangents[j].x;
            vertices[j].tangent.y = _aiMesh->mTangents[j].y;
            vertices[j].tangent.z = _aiMesh->mTangents[j].z;

            vertices[j].binormal.x = _aiMesh->mBitangents[j].x;
            vertices[j].binormal.y = _aiMesh->mBitangents[j].y;
            vertices[j].binormal.z = _aiMesh->mBitangents[j].z;



            //std::cout << "x = " << _aiMesh->mVertices[j].x << ", y = " << _aiMesh->mVertices[j].y << ", z = " << _aiMesh->mVertices[j].z << ", u = " << _aiMesh->mTextureCoords[0][j].x << ", v = " << _aiMesh->mTextureCoords[0][j].y << std::endl;
        }

        for (int j = 0; j < numIndices; j++)
        {
            face = &_aiMesh->mFaces[j];
            indexBuff.push_back(face->mIndices[0]);
            indexBuff.push_back(face->mIndices[1]);
            indexBuff.push_back(face->mIndices[2]);
        }

        numIndices *= 3;

#elif defined(OGL)
    
    for (int i = 0; i < numVertex; i++)
    {
        //Vertex
        vertices[i].vertex.x = _aiMesh->mVertices[i].x;
        vertices[i].vertex.y = _aiMesh->mVertices[i].y;
        vertices[i].vertex.z = _aiMesh->mVertices[i].z;

        
        //texture coords
        if (_aiMesh->HasTextureCoords(0))
        {
            vertices[i].TexCoords.x = _aiMesh->mTextureCoords[0][i].x;
            vertices[i].TexCoords.y = _aiMesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertices[i].TexCoords.x = 0;
            vertices[i].TexCoords.y = 0;
        }
        //std::cout << "x = " << _aiMesh->mVertices[j].x << ", y = " << _aiMesh->mVertices[j].y << ", z = " << _aiMesh->mVertices[j].z << ", u = " << _aiMesh->mTextureCoords[0][j].x << ", v = " << _aiMesh->mTextureCoords[0][j].y << std::endl;
    }

    
    for (int i = 0; i < numIndices; i++)
    {
        face = &_aiMesh->mFaces[i];
        indexBuff.push_back(face->mIndices[0]);
        indexBuff.push_back(face->mIndices[1]);
        indexBuff.push_back(face->mIndices[2]);
    }

    numIndices *= 3;

    return;
#endif
}

bool AssimpLoadModel::loadModel(std::string file)
{
    modelScene = importer.ReadFile(file, aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
        aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData | aiProcess_ValidateDataStructure | aiProcess_JoinIdenticalVertices | 0 );
    /*
    aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
        aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData | aiProcess_ValidateDataStructure | 0
    /**/
    /*
    aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices
        | aiProcess_CalcTangentSpace| aiProcess_OptimizeGraph | 0
    /**/
    /*
    Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices
    /**/

    if (modelScene)
    {
        m_GlobalInverseTransform = modelScene->mRootNode->mTransformation;
        m_GlobalInverseTransform.Inverse();
        processData();
    }
    else
    {

#if defined (DX11)
        MessageBoxA(NULL, importer.GetErrorString(), "Error: ", MB_ICONERROR); 

#endif
        return false;
    }

    return true;

    // ----------------------------------------

}

bool AssimpLoadModel::processData()
{
#if defined (DX11)
    bool repeat = true;

    nodeBuff.push_back(modelScene->mRootNode);

    while (repeat)
    {
        for (unsigned int a = 0; a < nodeBuff.size(); a++)
        {
            modelNode = nodeBuff.at(a);
            if (modelNode->mNumChildren > 0)
                for (unsigned int c = 0; c < modelNode->mNumChildren; c++)
                {
                    nodeBuff.push_back(modelNode->mChildren[c]);

                }

            else repeat = false;
        }
    }

    // Get node information from the root level (all nodes)
    for (unsigned int a = 0; a < nodeBuff.size(); a++)
    {
        modelNode = nodeBuff.at(a);

        if (modelNode->mNumMeshes > 0)
            for (unsigned int b = 0; b < modelNode->mNumMeshes; b++)
            {
                assimpGetMeshData(modelScene->mMeshes[b]);
                //std::cout << "::::::::PROCESSING =>" << modelScene->mMeshes[b]->mName;
            }
    }
#elif defined (OGL)


    m_Entries.resize(modelScene->mNumMeshes);
    m_Textures.resize(modelScene->mNumMaterials);
    
    std::vector<Vec3> Positions;
    std::vector<Vec3> Normals;
    std::vector<Vec2> TexCoords;
    std::vector<VertexBoneData> Bones;
    std::vector<unsigned int> Indices;

    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;

    unsigned int VerticesPerPrim = m_withAdjacencies ? 6 : 3;

    // Count the number of vertices and indices
    for (int i = 0; i < m_Entries.size(); i++)
    {
        m_Entries[i].MaterialIndex = modelScene->mMeshes[i]->mMaterialIndex;
        m_Entries[i].NumIndices = modelScene->mMeshes[i]->mNumFaces * VerticesPerPrim;
        m_Entries[i].BaseVertex = NumVertices;
        m_Entries[i].BaseIndex = NumIndices;

        NumVertices += modelScene->mMeshes[i]->mNumVertices;
        NumIndices += m_Entries[i].NumIndices;
    }

    // Reserve space in the vectors for the vertex attributes and indices
    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    TexCoords.reserve(NumVertices);
    Bones.resize(NumVertices);
    Indices.reserve(NumIndices);

    // Initialize the meshes in the scene one by one
    for (int i = 0; i < m_Entries.size(); i++)
    {
        const aiMesh* paiMesh = modelScene->mMeshes[i];
        InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
    }

    /*if (!InitMaterials())
    {
        return false;
    }/**/

    // Generate and populate the buffers with vertex attributes and the indices
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[VB_TYPES::POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[VB_TYPES::TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[VB_TYPES::NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[VB_TYPES::BONE_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[VB_TYPES::INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    //---

#endif

    return true;
}



void AssimpLoadModel::InitMesh(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<Vec3>& Positions, std::vector<Vec3>& Normals, std::vector<Vec2>& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    // Populate the vertex attribute vectors
    for (int i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Positions.push_back(Vec3(pPos->x, pPos->y, pPos->z));
        Normals.push_back(Vec3(pNormal->x, pNormal->y, pNormal->z));
        TexCoords.push_back(Vec2(pTexCoord->x, pTexCoord->y));
    }

    modelMesh = paiMesh;
    LoadBones(MeshIndex, paiMesh, Bones);

    if (m_withAdjacencies) 
    {
        //FindAdjacencies(paiMesh, Indices);
    }
    else {
        // Populate the index buffer
        for (int i = 0; i < paiMesh->mNumFaces; i++) {
            const aiFace& Face = paiMesh->mFaces[i];
            //assert(Face.mNumIndices == 3);
            Indices.push_back(Face.mIndices[0]);
            Indices.push_back(Face.mIndices[1]);
            Indices.push_back(Face.mIndices[2]);
        }
    }
}


void AssimpLoadModel::Render()
{
    /*
    glBindVertexArray(m_VAO);

    unsigned int Topology = m_withAdjacencies ? GL_TRIANGLES_ADJACENCY : GL_TRIANGLES;

    for (int i = 0; i < m_Entries.size(); i++) {
        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        assert(MaterialIndex < m_Textures.size());

        if (m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->Bind(COLOR_TEXTURE_UNIT);
        }

        glDrawElementsBaseVertex(Topology, m_Entries[i].NumIndices, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex), m_Entries[i].BaseVertex);
    }

    // Make sure the VAO is not changed from the outside    
    glBindVertexArray(0);/**/
}


/*
// ------------------ Bones
void AssimpLoadModel::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh,std::vector<VertexBoneData>& Bones)
{


    numBones = pMesh->mNumBones;
    
    for (int i = 0; i < numBones; i++) {
        unsigned int BoneIndex = 0;
        std::string BoneName(pMesh->mBones[i]->mName.data);

        if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
            // Allocate an index for a new bone
            BoneIndex = numBones;
            numBones++;
            BoneInfo bi;
            m_BoneInfo.push_back(bi);
            m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
            m_BoneMapping[BoneName] = BoneIndex;
        }
        else {
            BoneIndex = m_BoneMapping[BoneName];
        }

        for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
            unsigned int VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
            Bones[VertexID].AddBoneData(BoneIndex, Weight);
        }
    }


}

void AssimpLoadModel::BoneTransform(float TimeInSeconds, std::vector<aiMatrix4x4>& Transforms)
{
    aiMatrix4x4 Identity;
    //Identity.InitIdentity();
    
    float TicksPerSecond = modelScene->mAnimations[0]->mTicksPerSecond != 0 ? modelScene->mAnimations[0]->mTicksPerSecond : 25.0f;
    float TimeInTicks = TimeInSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, modelScene->mAnimations[0]->mDuration);

    ReadNodeHeirarchy(AnimationTime, modelScene->mRootNode, Identity);

    if (Transforms.size() != numBones)
        Transforms.resize(numBones);

    glm::mat4 model;

    for (int i = 0; i < numBones; i++) 
    {
        Transforms[i] = m_BoneInfo[i].FinalTransformation;
    }
}

void AssimpLoadModel::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform)
{
    std::string NodeName(pNode->mName.data);
    const aiAnimation* pAnimation = modelScene->mAnimations[0];

    aiMatrix4x4 NodeTransformation(pNode->mTransformation);

    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

    if (pNodeAnim) 
    {
        // Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        aiMatrix4x4 ScalingM;
        ScalingM.Scaling(aiVector3D(Scaling.x, Scaling.y, Scaling.z), ScalingM);
        //ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        aiMatrix4x4 RotationM = aiMatrix4x4(RotationQ.GetMatrix());

        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        aiMatrix4x4 TranslationM;
        //TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);

        // Combine the above transformations
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }

    aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

    if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
        unsigned int BoneIndex = m_BoneMapping[NodeName];
        m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
    }

    for (int i = 0; i < pNode->mNumChildren; i++) {
        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
}

void AssimpLoadModel::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) 
    {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}


void AssimpLoadModel::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

void AssimpLoadModel::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) 
    {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

aiNodeAnim* AssimpLoadModel::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
{
    for (int i = 0; i < pAnimation->mNumChannels; i++)
    {
        aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

        if (std::string(pNodeAnim->mNodeName.data) == NodeName)
        {
            return pNodeAnim;
        }
    }

    return nullptr;
}

unsigned int AssimpLoadModel::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);

    for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }

    return 0;
}

unsigned int AssimpLoadModel::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    for (int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
    {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
        {
            return i;
        }
    }

    return 0;
}

unsigned int AssimpLoadModel::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
    {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
        {
            return i;
        }
    }

    assert(0);
}/**/

Vertex* AssimpLoadModel::getVertexData()
{
    return vertices;
}

VertexLight* AssimpLoadModel::getVertexLightData()
{
    return vertexLight;
}

std::vector<unsigned short>* AssimpLoadModel::getIndexData()
{
    return &indexBuff;
}

/**/