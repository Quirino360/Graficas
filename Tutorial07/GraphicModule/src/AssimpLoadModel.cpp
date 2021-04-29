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

    numVertex = _aiMesh->mNumVertices;
    numIndices = _aiMesh->mNumFaces;

    vertices = new Vertex[numVertex];
    indices = new unsigned short[numIndices];

#if defined(DX11)
        for (int j = 0; j < numVertex; j++)
        {
            //Vertex
            vertices[j].vertex.x = _aiMesh->mVertices[j].x;
            vertices[j].vertex.y = _aiMesh->mVertices[j].y;
            vertices[j].vertex.z = _aiMesh->mVertices[j].z;

            //Normales
            vertices[j].normals.x = _aiMesh->mNormals->x;
            vertices[j].normals.y = _aiMesh->mNormals->y;
            vertices[j].normals.z = _aiMesh->mNormals->z;

            //uv
            if (_aiMesh->HasTextureCoords(0)) 
            {
                vertices[j].uvs.x = _aiMesh->mTextureCoords[0][j].x;
                vertices[j].uvs.y = _aiMesh->mTextureCoords[0][j].y;
            }
            else
            {
                vertices[j].uvs.x = 0;
                vertices[j].uvs.y = 0;
            }
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
    numIndices *= 3;


    return;
#endif
}

bool AssimpLoadModel::loadModel(std::string file)
{
    modelScene = importer.ReadFile(file, aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
        aiProcess_CalcTangentSpace |     aiProcess_GenSmoothNormals |    aiProcess_Triangulate | aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData |  aiProcess_ValidateDataStructure | 0

    );

    if (!modelScene)
    {
#if defined (DX11)
        MessageBoxA(NULL, importer.GetErrorString(), "Error: ", MB_ICONERROR); 
#endif
        return false;

    }
    else
        processData();

    return true;
}

bool AssimpLoadModel::processData()
{
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
            for (unsigned int b = 0; b < modelNode->mNumMeshes; b++) {
                assimpGetMeshData(modelScene->mMeshes[b]);
                //std::cout << "::::::::PROCESSING =>" << modelScene->mMeshes[b]->mName;
            }
    }
    return true;
}

Vertex* AssimpLoadModel::getVertexData()
{
    return vertices;
}

std::vector<unsigned short>* AssimpLoadModel::getIndexData()
{
    return &indexBuff;
}
