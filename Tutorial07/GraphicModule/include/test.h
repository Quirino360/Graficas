#pragma once
#include <windows.h>
#include "AssimpLoadModel.h"
#include <vector>
#include <map>

#if defined(OGL) || defined(DX11)
#include <FreeImage.h>
#endif

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

#include "EffectS.h"
#include "Camera.h"
#include "Mesh.h"
#include "Buffer.h"
#include "Texture2D.h"
#include "RenderManager.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Shader.h"

#include "Structs.h"

namespace GraphicsModule 
{
    class test
    {
    public:
#if defined(DX11)
        
        // New Shit
        EffectS m_effect;

        std::vector<Buffer> g_buffers;
        std::vector<bMatrix> m_matrix;
                                                           
        std::vector<bFloat4> m_floats4;
        std::vector<bFloat3> m_floats3;
        std::vector<bFloat2> m_floats2;
        std::vector<bFloat> m_floats;

        std::vector<bInt4> m_ints4;
        std::vector<bInt3> m_ints3;
        std::vector<bInt2> m_ints2;
        std::vector<bInt> m_ints;

        std::vector<bBool> m_bools;

        std::vector<bResourceView> m_resourceViews; // Textures (ej. t0) // Estos son buffers
        std::vector<bSampler> mSamplers; // Samplers (ej. s0) // Estos son buffers
        std::vector<bRenderTarget> renderTargetsView;
        
        //std::vector<StreamMap> m_streamMaps; // InputLayout


        // Effect pass and 

        D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
        D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;

        ID3D11Device* g_pd3dDevice = NULL;
        ID3D11DeviceContext* g_pImmediateContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        RenderManager renderManager;

        DepthStencilView* g_pDepthStencilView = NULL;

        float t = 0;
        ID3D11SamplerState* g_pSamplerLinear = NULL;  //s0
        ID3D11SamplerState* sampnormalMap = NULL;  //s1
        ID3D11SamplerState* samplerSpecular = NULL;  //s2

        // ----- Matrices
        XMMATRIX g_World;
        XMMATRIX g_View;
        XMMATRIX g_Projection;

        ID3D11RasterizerState* g_Rasterizer = NULL;

        // ----------   Buffers
        Buffer* g_pVertexBuffer = nullptr; //
        Buffer* g_pIndexBuffer = nullptr; //

        // View
        Buffer* g_pCBNeverChanges = nullptr; // b0 
        cbNeverChanges m_cbNeverChanges; 

        // Projection
        Buffer* g_pCBChangeOnResize = nullptr; // b1
        cbChangeOnResize m_cbChangesOnResize;

        // World
        Buffer* g_pCBChangesEveryFrame = nullptr; // b2
        CBChangesEveryFrame m_cbChangesEveryFrame;

        // -----  Light Buffers
        Buffer* g_DirLightBuffer = nullptr; // b3
        DirLight m_DirLightBuffer;

        Buffer* g_PointLightBuffer = nullptr; // b4
        PointLight m_PointLightBuffer;

        Buffer* g_SpotLightBuffer = nullptr; // b5
        spotLight m_SpotLightBuffer;

        Buffer* g_AmbientLightBuffer = nullptr; // b6
        Ambient m_AmbientLightBuffer;

        Buffer* g_SpecularBuffer = nullptr; // b7
        Specular m_SpecularBuffer;

        Buffer* g_ShiniesBuffer = nullptr; // b8
        Shinies m_ShiniesBuffer;

        Buffer* g_DiffuseBuffer = nullptr; // b9
        Diffuse m_DiffuseBuffer;

        // Load model with assimp
        AssimpLoadModel aLoadModel;

        Camera                              camera;
        Mesh                                mesh;
        bool                                cameraChange = true;
        bool                                mouseMove = false;
        LPPOINT                             newCursor = new POINT();
        LPPOINT                             oldCursor = new POINT();

        // ----- Textures
        Texture2D* Texture = nullptr; 

        ID3D11ShaderResourceView* ResourceViewAlbedo = nullptr; //t0
        ID3D11ShaderResourceView* ResourceViewNormal = nullptr; //t1 
        ID3D11ShaderResourceView* ResourceViewSpecular = nullptr; //t2

        RenderTargetView* RenderTargetV = NULL;


#elif defined(OGL)
    public:
        AssimpLoadModel aLoadModel;

        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        unsigned int VAO;
        unsigned int VBO;

        Shader ourShader;

        unsigned int texture;
        unsigned int texture2;

    private:
    public:
    private:
#endif

    public:
        HRESULT InitDevice(HWND _hwnd);

        void Update();
        void Render();

        void CleanupDevice();

        HWND m_hwnd;

#if defined(DX11)
    public:
        //HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        void InitVariables();
#endif
    };

    extern test& GetTestObj(HWND _hwnd = NULL);

}