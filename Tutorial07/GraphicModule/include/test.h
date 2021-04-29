#pragma once
#include <windows.h>
#include "AssimpLoadModel.h"

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

#include"Camera.h"
#include "Mesh.h"
#include "Buffer.h"
#include "Texture2D.h"
#include "RenderManager.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Shader.h"

#if defined(OGL) || defined(DX11)
#include <FreeImage.h>
#endif

namespace GraphicsModule
{
    

    struct VIEWPORT
    {
#if defined(DX11)
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;
#endif
    };

    struct SimpleVertex
    {
#if defined(DX11)
        XMFLOAT3 Pos;
        XMFLOAT2 Tex;
        XMFLOAT3 Normal;
#endif
    };

    struct DirLight
    {
#if defined(DX11)
        XMFLOAT4 dir;
#endif
    };

    struct CBNeverChanges
    {
#if defined(DX11)
        XMMATRIX mView;
#endif
    };

    struct CBChangeOnResize
    {
#if defined(DX11)
        XMMATRIX mProjection;
#endif
    };

    struct CBChangesEveryFrame
    {
#if defined(DX11)
        XMMATRIX mWorld;
        XMFLOAT4 vMeshColor;
#endif
    };

    class test
    {
    public:
#if defined(DX11)
        D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
        D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;

        ID3D11Device* g_pd3dDevice = NULL;
        ID3D11DeviceContext* g_pImmediateContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        RenderManager renderManager;



        DepthStencilView* g_pDepthStencilView = NULL;

        ID3D11VertexShader* g_pVertexShader = NULL;
        ID3D11PixelShader* g_pPixelShader = NULL;
        ID3D11InputLayout* g_pVertexLayout = NULL;

        Buffer* g_pVertexBuffer = nullptr; //
        Buffer* g_pIndexBuffer = nullptr; //
        Buffer* g_pCBNeverChanges = nullptr; //
        Buffer* g_pCBChangeOnResize = nullptr; //
        Buffer* g_pCBChangesEveryFrame = nullptr; //



        ID3D11SamplerState* g_pSamplerLinear = NULL;
        XMMATRIX                            g_World;
        XMMATRIX                            g_View;
        XMMATRIX                            g_Projection;
        XMFLOAT4                            g_vMeshColor;

        Buffer* g_pVertexBuffer2 = nullptr; //
        Buffer* g_pIndexBuffer2 = nullptr; //

        ID3D11VertexShader* g_pVertexShader2 = NULL;
        ID3D11PixelShader* g_pPixelShader2 = NULL;
        ID3D11RasterizerState* g_Rasterizer = NULL;
        ID3D11RasterizerState* g_Rasterizer2 = NULL;
        ID3D11InputLayout* g_pVertexLayout2 = NULL;


        //---------------------------------      ---------------------------------//
        Buffer* g_DirLightBuffer = nullptr; //directional light
        DirLight m_DirLightBuffer;

        AssimpLoadModel aLoadModel;
        Camera                              camera;
        Mesh                                mesh;
        bool                                cameraChange = true;
        bool                                mouseMove = false;
        LPPOINT                             newCursor = new POINT();
        LPPOINT                             oldCursor = new POINT();

        // -------------------------------------------------------- Inlcuion de texturas ---------------------------------------------------- //
        Texture2D* Texture = nullptr; //

        ID3D11ShaderResourceView* ShaderResourceView = NULL;
        ID3D11ShaderResourceView* ResorceView1 = NULL;
        RenderTargetView* RenderTargetView1 = NULL;


        //ID3D11ShaderResourceView* ResorceView2 = NULL;
        //RenderTargetView* RenderTargetView2 = NULL;

        //ID3D11ShaderResourceView* ResorceView3 = NULL;
        //RenderTargetView* RenderTargetView3 = NULL;

        //ID3D11ShaderResourceView* ResorceView4 = NULL;
        //RenderTargetView* RenderTargetView4 = NULL;
#elif defined(OGL)
    public:
        AssimpLoadModel aLoadModel;
        Shader ourShader;

        unsigned int VBO, VAO;

        unsigned int texture;
        unsigned int texture2;
#endif

    public:


        HRESULT InitDevice(HWND _hwnd);

        void Update();
        void Render();

        void CleanupDevice();

        HWND m_hwnd;

#if defined(DX11)
    public:
        HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        void InitVariables();
#endif
    };

    extern test& GetTestObj(HWND _hwnd);

}