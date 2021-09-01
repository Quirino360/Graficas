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

    // -------------------- Buffers --------------------//
    struct cbNeverChanges // b0
    {
#if defined(DX11)
        XMMATRIX mView;
#endif
    };

    struct cbChangeOnResize // b1
    {
#if defined(DX11)
        XMMATRIX mProjection;
#endif
    };

    // cbChangesEveryFrame b2 (it in a class I dont Remember, i think mesh)

    struct DirLight // b3
    {
#if defined(DX11)
        XMFLOAT4 dir;
        XMFLOAT4 lightDirColor;
#endif
    };

    struct PointLight // b4
    {
#if defined(DX11)
        XMFLOAT4 pointLightColor;
        XMFLOAT3 pointLightPos;
        FLOAT  pointLightAtt;
#endif
    };

    struct spotLight // b5
    {
#if defined(DX11)
        XMFLOAT4 spotLightColor;
        XMFLOAT4 spotLightPos;
        XMFLOAT4 spotLightDir;
        FLOAT  SpotlightAtt;
        FLOAT  spotLightInner;
        FLOAT  spotLightOutner;
        FLOAT  n;
#endif
    };

    struct Ambient // b6
    {
#if defined(DX11)
        XMFLOAT4 ambientColor;
        XMFLOAT3 n1;
        FLOAT kAmbient;
#endif
    };

    struct Specular // b7
    {
#if defined(DX11)
        XMFLOAT3 n2;
        FLOAT kSpecular;
#endif
    };

 //#if defined(PHONG) || defined(BLINN_PHONG)
    struct Shinies // b8
    {
#if defined(DX11)
        XMFLOAT3 n3;
        FLOAT shininess;
#endif
    };

    struct Diffuse // b9
    {
#if defined(DX11)
        XMFLOAT3 n4;
        FLOAT kDiffuse;
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
        ID3D11SamplerState* g_pSamplerLinear = NULL;  //s0
        ID3D11SamplerState* sampnormalMap = NULL;  //s1
        ID3D11SamplerState* samplerSpecular = NULL;  //s2

        XMMATRIX                            g_View;
        XMMATRIX                            g_Projection;

        ID3D11RasterizerState* g_Rasterizer = NULL;

        //---------------------------------   Buffers   ---------------------------------//
        Buffer* g_pVertexBuffer = nullptr; //
        Buffer* g_pIndexBuffer = nullptr; //

        Buffer* g_pCBNeverChanges = nullptr; // b0

        Buffer* g_pCBChangeOnResize = nullptr; // b1
        cbChangeOnResize cbChangesOnResize;

        Buffer* g_pCBChangesEveryFrame = nullptr; // b2

        //---------------------------------  Light Buffers    ---------------------------------//
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


        AssimpLoadModel aLoadModel;
        Camera                              camera;
        Mesh                                mesh;
        bool                                cameraChange = true;
        bool                                mouseMove = false;
        LPPOINT                             newCursor = new POINT();
        LPPOINT                             oldCursor = new POINT();

        // -------------------------------------------------------- Inlcuion de texturas ---------------------------------------------------- //
        //ID3D11ShaderResourceView* ShaderResourceView = NULL;
        Texture2D* Texture = nullptr; //

        ID3D11ShaderResourceView* ResourceViewAlbedo = NULL; //t0
        ID3D11ShaderResourceView* ResourceViewNormal = NULL; //t1 
        ID3D11ShaderResourceView* ResourceViewSpecular = NULL; //t2

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