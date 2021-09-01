#pragma once
#include <windows.h>
#include "AssimpLoadModel.h"


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
#include "Buffers.h"

namespace GraphicsModule
{

    struct VIEWPORT
    {
#if defined(DX11)
        FLOAT TopLeftX;
        FLOAT TopLeftY;
        FLOAT Width;
        FLOAT Height;
        FLOAT MinDepth;
        FLOAT MaxDepth;
#endif
    };

    class test
    {
    public:
#if defined(DX11)
        
        EffectS m_effect;
        Shader shader;

        D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
        D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;

        ID3D11Device* g_pd3dDevice = NULL;
        ID3D11DeviceContext* g_pImmediateContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        RenderManager renderManager;

        DepthStencilView* g_pDepthStencilView = NULL;

        float t = 0;


        ID3D11RasterizerState* g_Rasterizer = NULL;

        // ---------------------------------   Buffers   --------------------------------- //
        Buffer* g_pVertexBuffer = nullptr; 
        Buffer* g_pIndexBuffer = nullptr; 

        Buffer* g_pCBNeverChanges = nullptr; // b0
        XMMATRIX g_View;

        Buffer* g_pCBChangeOnResize = nullptr; // b1
        cbChangeOnResize cbChangesOnResize;

        Buffer* g_pCBChangesEveryFrame = nullptr; // b2
        XMMATRIX g_Projection;

        // ---------------------------------  Light Buffers    --------------------------------- //
        Buffer* g_DirLightBuffer = nullptr; // b4
        DirLight m_DirLightBuffer;

        Buffer* g_PointLightBuffer = nullptr; // b5
        PointLight m_PointLightBuffer;

        Buffer* g_SpotLightBuffer = nullptr; // b6
        spotLight m_SpotLightBuffer;

        Buffer* g_AmbientLightBuffer = nullptr; // b7
        Ambient m_AmbientLightBuffer;

        Buffer* g_SpecularBuffer = nullptr; // b8
        Specular m_SpecularBuffer;

        Buffer* g_ShiniesBuffer = nullptr; // b9
        Shinies m_ShiniesBuffer;

        Buffer* g_DiffuseBuffer = nullptr; // b10
        Diffuse m_DiffuseBuffer;


        // --------------------------------- Textures --------------------------------- //
        //ID3D11ShaderResourceView* ShaderResourceView = NULL;
        Texture2D* Texture = nullptr; //

        ID3D11ShaderResourceView* ResourceViewAlbedo = NULL; //t0
        ID3D11ShaderResourceView* ResourceViewNormal = NULL; //t2
        ID3D11ShaderResourceView* ResourceViewSpecular = NULL; //t3
        ID3D11ShaderResourceView* ResourceViewPosition = NULL; //t4

        ID3D11SamplerState* g_pSamplerLinear = NULL;  //s0
        ID3D11SamplerState* sampnormalMap = NULL;  //s1
        ID3D11SamplerState* samplerSpecular = NULL;  //s2

        RenderTargetView* RenderTargetV = NULL;



        AssimpLoadModel aLoadModel;
        Camera                              camera;
        Mesh                                mesh;
        bool                                cameraChange = true;
        bool                                mouseMove = false;
        LPPOINT                             newCursor = new POINT();
        LPPOINT                             oldCursor = new POINT();



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