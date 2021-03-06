#include "test.h"


namespace GraphicsModule
{
#if defined(DX11)
    HRESULT test::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
    {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows
        // the shaders to be optimized and to run exactly the way they will run in
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ID3DBlob* pErrorBlob;
        hr = D3DX11CompileFromFileA(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
            dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
        if (FAILED(hr))
        {
            if (pErrorBlob != NULL)
                OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
            if (pErrorBlob) pErrorBlob->Release();
            return hr;
        }
        if (pErrorBlob) pErrorBlob->Release();

        return S_OK;
    }


    void test::InitVariables()
    {
        Texture = new Texture2D();
        g_pVertexBuffer = new Buffer();
        g_pIndexBuffer = new Buffer();
        g_pCBNeverChanges = new Buffer();
        g_pCBChangeOnResize = new Buffer();
        g_pCBChangesEveryFrame = new Buffer();
        g_pVertexBuffer2 = new Buffer();
        g_pIndexBuffer2 = new Buffer();
        RenderTargetView1 = new RenderTargetView();
        RenderTargetView2 = new RenderTargetView();
        RenderTargetView3 = new RenderTargetView();
        RenderTargetView4 = new RenderTargetView();
        g_pDepthStencilView = new DepthStencilView();
    }
#endif

    HRESULT test::InitDevice(HWND _hwnd)
    {
#if defined(DX11)

        InitVariables();

        m_hwnd = _hwnd;

        HRESULT hr = S_OK;

        RECT rc;
        GetClientRect(m_hwnd, &rc);
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE(driverTypes);

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = m_hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
        {
            g_driverType = driverTypes[driverTypeIndex];
            hr = renderManager.CreateDeviceAndSwapChainDX11(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                D3D11_SDK_VERSION, &sd, &renderManager.getSwapChainDX11(), &renderManager.getDeviceDX11(), &g_featureLevel, &renderManager.getDeviceContextDX11());


            if (SUCCEEDED(hr))
                break;
        }
        if (FAILED(hr))
            return hr;

        // Create a render target view
        //ID3D11Texture2D* pBackBuffer = NULL;
        Texture2D* pBackBuffer = new Texture2D();
            

        hr = renderManager.GetBufferDX11(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer->getTextureDX11());
        if (FAILED(hr))
            return hr;
        hr = renderManager.CreateRenderTargetViewDX11(pBackBuffer->getTextureDX11(), NULL, &RenderTargetView1->getRenderTargetViewDX11());
        pBackBuffer->getTextureDX11()->Release();
        if (FAILED(hr))
            return hr;

        // Create depth stencil texture
        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = width;
        descDepth.Height = height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_R32_TYPELESS;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = renderManager.CreateTexture2DDX11(&descDepth, NULL, &Texture->getTextureDX11());
        if (FAILED(hr))
            return hr;

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = DXGI_FORMAT_D32_FLOAT;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = renderManager.CreateDepthStencilViewDX11(Texture->getTextureDX11(), &descDSV, &g_pDepthStencilView->getyDepthStencilViewDX11());
        if (FAILED(hr))
            return hr;

        // and the resource view for the shader
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1; // same as orig texture
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &srvDesc, &ShaderResourceView);
        if (FAILED(hr))
            return hr;

        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView1->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());

        // Setup the viewport
        //D3D11_VIEWPORT vp;
        VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;

        renderManager.RSSetViewportsDX11(1, reinterpret_cast<D3D11_VIEWPORT*>(&vp));

        // Compile the vertex shader
        ID3DBlob* pVSBlob = NULL;
        hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        hr = renderManager.CreateVertexShaderDX11(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE(layout);

        // Create the input layout
        hr = renderManager.CreateInputLayoutDX11(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Compile the vertex shader
        ID3DBlob* pVSBlob2 = NULL;
        hr = CompileShaderFromFile("Limpio.fx", "VS", "vs_4_0", &pVSBlob2);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        hr = renderManager.CreateVertexShaderDX11(pVSBlob2->GetBufferPointer(), pVSBlob2->GetBufferSize(), NULL, &g_pVertexShader2);
        if (FAILED(hr))
        {
            pVSBlob2->Release();
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout2[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements2 = ARRAYSIZE(layout2);

        // Create the input layout
        hr = renderManager.CreateInputLayoutDX11(layout2, numElements2, pVSBlob2->GetBufferPointer(), pVSBlob2->GetBufferSize(), &g_pVertexLayout2);
        pVSBlob2->Release();
        if (FAILED(hr))
            return hr;

        // Compile the pixel shader
        ID3DBlob* pPSBlob = NULL;
        hr = CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = renderManager.CreatePixelShaderDX11(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Compile the pixel shader
        ID3DBlob* pPSBlob2 = NULL;
        hr = CompileShaderFromFile("Limpio.fx", "PS", "ps_4_0", &pPSBlob2);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = renderManager.CreatePixelShaderDX11(pPSBlob2->GetBufferPointer(), pPSBlob2->GetBufferSize(), NULL, &g_pPixelShader2);
        pPSBlob2->Release();
        if (FAILED(hr))
            return hr;

        // Create vertex buffer
        Vertex vertices[] =
        {
            { Vec3{-1.0f, 1.0f, -1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{1.0f, 1.0f, -1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{1.0f, 1.0f, 1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{-1.0f, 1.0f, 1.0f}, Vec2{0.0f, 1.0f} },

            { Vec3{-1.0f, -1.0f, -1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{1.0f, -1.0f, -1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{1.0f, -1.0f, 1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{-1.0f, -1.0f, 1.0f}, Vec2{0.0f, 1.0f} },

            { Vec3{-1.0f, -1.0f, 1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{-1.0f, -1.0f, -1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{-1.0f, 1.0f, -1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{-1.0f, 1.0f, 1.0f}, Vec2{0.0f, 1.0f} },

            { Vec3{1.0f, -1.0f, 1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{1.0f, -1.0f, -1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{1.0f, 1.0f, -1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{1.0f, 1.0f, 1.0f}, Vec2{0.0f, 1.0f} },

            { Vec3{-1.0f, -1.0f, -1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{1.0f, -1.0f, -1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{1.0f, 1.0f, -1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{-1.0f, 1.0f, -1.0f}, Vec2{0.0f, 1.0f} },

            { Vec3{-1.0f, -1.0f, 1.0f}, Vec2{0.0f, 0.0f} },
            { Vec3{1.0f, -1.0f, 1.0f}, Vec2{1.0f, 0.0f} },
            { Vec3{1.0f, 1.0f, 1.0f}, Vec2{1.0f, 1.0f} },
            { Vec3{-1.0f, 1.0f, 1.0f}, Vec2{0.0f, 1.0f} },
        };
        mesh.setVetices(vertices, 24);

        //D3D11_BUFFER_DESC bd;
        BUFFER_DESC_DX11 bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT_DX11;
        bd.ByteWidth = sizeof(Vertex) * 24;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = mesh.getVertices();
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &g_pVertexBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create index buffer
        // Create vertex buffer
        unsigned short indices[] =
        {
            3,1,0,
            2,1,3,

            6,4,5,
            7,4,6,

            11,9,8,
            10,9,11,

            14,12,13,
            15,12,14,

            19,17,16,
            18,17,19,

            22,20,21,
            23,20,22
        };
        mesh.setIndexBuffer(indices, 36);

        bd.Usage = D3D11_USAGE_DEFAULT_DX11;
        bd.ByteWidth = sizeof(unsigned short) * 36;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        InitData.pSysMem = mesh.getIndexBuffer();
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &g_pIndexBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Set primitive topology
        renderManager.IASetPrimitiveTopologyDX11(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Create the constant buffers
        bd.Usage = D3D11_USAGE_DEFAULT_DX11;
        bd.ByteWidth = sizeof(CBNeverChanges);
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = 0;
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBNeverChanges->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        bd.ByteWidth = sizeof(CBChangeOnResize);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBChangeOnResize->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        bd.ByteWidth = sizeof(CBChangesEveryFrame);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBChangesEveryFrame->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Load the Texture

        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), "ahegao.dds", NULL, NULL, &ResorceView1, NULL);
        if (FAILED(hr))
            return hr;

        // Create the sample state
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
        hr = renderManager.CreateSamplerStateDX11(&sampDesc, &g_pSamplerLinear);
        if (FAILED(hr))
            return hr;

        // Initialize the world matrices
        g_World = XMMatrixIdentity();

        // Initialize the view matrix
        camera.setEye(0.0f, 3.0f, -6.0f);
        camera.setAt(0.0f, 1.0f, 0.0f);
        camera.setUp(0.0f, 1.0f, 0.0f);
        camera.setViewMatrix();

        g_View = XMMATRIX(camera.getViewMatrix().matrix4);



        CBNeverChanges cbNeverChanges;
        cbNeverChanges.mView = XMMatrixTranspose(g_View);
        renderManager.UpdateSubresourceDX11(g_pCBNeverChanges->getyBufferDX11(), 0, NULL, &cbNeverChanges, 0, 0);

        // Initialize the projection matrix
        camera.setMatrixPerspective(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
        camera.setMatrixOrthographic(width / 100, height / 100, 0.01f, 100.0f);
        if (cameraChange)
        {
            g_Projection = XMMATRIX(camera.getMatrixPerspective().matrix4);
        }
        else
        {
            g_Projection = XMMATRIX(camera.getMatrixOrthographic().matrix4);
        }

        CBChangeOnResize cbChangesOnResize;
        cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
        renderManager.UpdateSubresourceDX11(g_pCBChangeOnResize->getyBufferDX11(), 0, NULL, &cbChangesOnResize, 0, 0);


        // create rasterizer state
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.CullMode = D3D11_CULL_BACK;
        desc.FillMode = D3D11_FILL_SOLID;
        hr = renderManager.CreateRasterizerStateDX11(&desc, &g_Rasterizer);
        if (FAILED(hr))
            return hr;

        desc.CullMode = D3D11_CULL_NONE;
        hr = renderManager.CreateRasterizerStateDX11(&desc, &g_Rasterizer2);
        if (FAILED(hr))
            return hr;







        // -----------------------------------------------------------------------------------------------------------------------------------------------------------/ 
        // ---------------------------------------------- set render target View, Shader ResourceView, and Texture ---------------------------------------------------/ 

        // ----------------------------------------------------------  texture 2 ---------------------------------------------------------- //
        Texture->ReleaseDX11();
        // Create rt texture
        D3D11_TEXTURE2D_DESC descTextRT2;
        ZeroMemory(&descTextRT2, sizeof(descTextRT2));
        descTextRT2.Width = width;
        descTextRT2.Height = height;
        descTextRT2.MipLevels = 1;
        descTextRT2.ArraySize = 1;
        descTextRT2.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descTextRT2.SampleDesc.Count = 1;
        descTextRT2.SampleDesc.Quality = 0;
        descTextRT2.Usage = D3D11_USAGE_DEFAULT;
        descTextRT2.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        descTextRT2.CPUAccessFlags = 0;
        descTextRT2.MiscFlags = 0;
        hr = renderManager.CreateTexture2DDX11(&descTextRT2, NULL, &Texture->getTextureDX11());
        if (FAILED(hr))
            return hr;

        // create the rt Shader resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT2;
        ZeroMemory(&descViewRT2, sizeof(descViewRT2));
        descViewRT2.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descViewRT2.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        descViewRT2.Texture2D.MostDetailedMip = 0;
        descViewRT2.Texture2D.MipLevels = 1;
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &descViewRT2, &ResorceView2);
        if (FAILED(hr))
            return hr;

        // Create the render target view
        hr = renderManager.CreateRenderTargetViewDX11(Texture->getTextureDX11(), NULL, &RenderTargetView2->getRenderTargetViewDX11());
        if (FAILED(hr))
            return hr;

        // ----------------------------------------------------------  texture 3 ---------------------------------------------------------- //
        Texture->ReleaseDX11();
        // Create rt texture
        D3D11_TEXTURE2D_DESC descTextRT3;
        ZeroMemory(&descTextRT3, sizeof(descTextRT3));
        descTextRT3.Width = width;
        descTextRT3.Height = height;
        descTextRT3.MipLevels = 1;
        descTextRT3.ArraySize = 1;
        descTextRT3.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descTextRT3.SampleDesc.Count = 1;
        descTextRT3.SampleDesc.Quality = 0;
        descTextRT3.Usage = D3D11_USAGE_DEFAULT;
        descTextRT3.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        descTextRT3.CPUAccessFlags = 0;
        descTextRT3.MiscFlags = 0;
        hr = renderManager.CreateTexture2DDX11(&descTextRT3, NULL, &Texture->getTextureDX11());
        if (FAILED(hr))
            return hr;

        // create the rt Shader resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT3;
        ZeroMemory(&descViewRT3, sizeof(descViewRT3));
        descViewRT3.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descViewRT3.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        descViewRT3.Texture2D.MostDetailedMip = 0;
        descViewRT3.Texture2D.MipLevels = 1;
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &descViewRT3, &ResorceView3);
        if (FAILED(hr))
            return hr;

        // Create the render target view
        hr = renderManager.CreateRenderTargetViewDX11(Texture->getTextureDX11(), NULL, &RenderTargetView3->getRenderTargetViewDX11());
        if (FAILED(hr))
            return hr;

        // ----------------------------------------------------------  texture 4 ---------------------------------------------------------- //
        Texture->ReleaseDX11();

        // Create rt texture
        D3D11_TEXTURE2D_DESC descTextRT4;
        ZeroMemory(&descTextRT4, sizeof(descTextRT4));
        descTextRT4.Width = width;
        descTextRT4.Height = height;
        descTextRT4.MipLevels = 1;
        descTextRT4.ArraySize = 1;
        descTextRT4.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descTextRT4.SampleDesc.Count = 1;
        descTextRT4.SampleDesc.Quality = 0;
        descTextRT4.Usage = D3D11_USAGE_DEFAULT;
        descTextRT4.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        descTextRT4.CPUAccessFlags = 0;
        descTextRT4.MiscFlags = 0;
        hr = renderManager.CreateTexture2DDX11(&descTextRT4, NULL, &Texture->getTextureDX11());
        if (FAILED(hr))
            return hr;

        // create the rt Shader resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT4;
        ZeroMemory(&descViewRT4, sizeof(descViewRT4));
        descViewRT4.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descViewRT4.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        descViewRT4.Texture2D.MostDetailedMip = 0;
        descViewRT4.Texture2D.MipLevels = 1;
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &descViewRT4, &ResorceView4);
        if (FAILED(hr))
            return hr;

        // Create the render target view
        hr = renderManager.CreateRenderTargetViewDX11(Texture->getTextureDX11(), NULL, &RenderTargetView4->getRenderTargetViewDX11());
        if (FAILED(hr))
            return hr;


#endif
        return S_OK;
    }

    void test::Update()
    {
#if defined(DX11)
        // Update our time
        static float t = 0.0f;
        if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
        {
            t += (float)XM_PI * 0.0125f;
        }
        else
        {
            static DWORD dwTimeStart = 0;
            DWORD dwTimeCur = GetTickCount();
            if (dwTimeStart == 0)
                dwTimeStart = dwTimeCur;
            t = (dwTimeCur - dwTimeStart) / 1000.0f;
        }

        *oldCursor = *newCursor;
        GetCursorPos(newCursor);
        camera.RotateCamera(Vector3(newCursor->x, newCursor->y, 0), Vector3(oldCursor->x, oldCursor->y, 0));


        // Modify the color
        g_vMeshColor.x = 0.5;
        g_vMeshColor.y = 0.5;
        g_vMeshColor.z = 0.5;


        //
        // Clear the back buffer
        //


        //
        // Update variables that change once per frame
        //

        CBNeverChanges cbNeverChanges;
        cbNeverChanges.mView = XMMatrixTranspose(g_View);
        renderManager.UpdateSubresourceDX11(g_pCBNeverChanges->getyBufferDX11(), 0, NULL, &cbNeverChanges, 0, 0);

        CBChangeOnResize cbChangesOnResize;
        cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
        renderManager.UpdateSubresourceDX11(g_pCBChangeOnResize->getyBufferDX11(), 0, NULL, &cbChangesOnResize, 0, 0);

        // Move the mouse updating the position
        g_View = XMMATRIX(camera.getViewMatrix().matrix4);
        cbNeverChanges.mView = XMMatrixTranspose(g_View);
        renderManager.UpdateSubresourceDX11(g_pCBNeverChanges->getyBufferDX11(), 0, NULL, &cbNeverChanges, 0, 0);
#endif
    }

    void test::Render()
    {
#if defined(DX11)

        // Update our time
        static float t = 0.0f;
        if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
        {
            t += (float)XM_PI * 0.0125f;
        }
        else
        {
            static DWORD dwTimeStart = 0;
            DWORD dwTimeCur = GetTickCount();
            if (dwTimeStart == 0)
                dwTimeStart = dwTimeCur;
            t = (dwTimeCur - dwTimeStart) / 1000.0f;
        }

        //g_World = XMMatrixRotationY(t);


        //Set index buffer



        UINT stride = sizeof(SimpleVertex);
        UINT offset = 0;

        // Set the input layout

        renderManager.IASetInputLayoutDX11(g_pVertexLayout);
        renderManager.RSSetStateDX11(g_Rasterizer);
        renderManager.IASetVertexBuffersDX11(0, 1, &g_pVertexBuffer->getyBufferDX11(), &stride, &offset);
        renderManager.IASetIndexBufferDX11(g_pIndexBuffer->getyBufferDX11(), DXGI_FORMAT_R16_UINT, 0);
        renderManager.VSSetShaderDX11(g_pVertexShader, NULL, 0);
        renderManager.VSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.PSSetShaderDX11(g_pPixelShader, NULL, 0);
        renderManager.PSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.PSSetSamplersDX11(0, 1, &g_pSamplerLinear);
        renderManager.DrawIndexedDX11(36, 0, 0);





        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
        CBChangesEveryFrame cb;

        // ----------------------------------------------- Cubes RenderTargetVview2 ---------------------------------------------------------//
        renderManager.ClearRenderTargetViewDX11(RenderTargetView2->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView2->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView1); //set sahder resorce view 1
        g_World = XMMatrixTranslation(0, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        // ----------------------------------------------- Cubes RenderTargetVview3 ---------------------------------------------------------//
        renderManager.ClearRenderTargetViewDX11(RenderTargetView3->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView3->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView2); //set sahder resorce view 2
        g_World = XMMatrixTranslation(0, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView1); //set sahder resorce view 1
        g_World = XMMatrixTranslation(3, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);

        // ----------------------------------------------- Cubes RenderTargetVview4 ---------------------------------------------------------//
        renderManager.ClearRenderTargetViewDX11(RenderTargetView4->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView4->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView3); //set sahder resorce view 3
        g_World = XMMatrixTranslation(0, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView2); //set sahder resorce view 2
        g_World = XMMatrixTranslation(3, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView1); //set sahder resorce view 1
        g_World = XMMatrixTranslation(0, 3, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        // ----------------------------------------------- Cubes RenderTargetVview1 ---------------------------------------------------------//
        renderManager.ClearRenderTargetViewDX11(RenderTargetView1->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView1->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView4); //set sahder resorce view 4
        g_World = XMMatrixTranslation(0, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView3); //set sahder resorce view 3
        g_World = XMMatrixTranslation(3, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView2); //set sahder resorce view 2
        g_World = XMMatrixTranslation(0, 3, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView1); //set sahder resorce view 1
        g_World = XMMatrixTranslation(-3, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);
        renderManager.DrawIndexedDX11(36, 0, 0);





        // Render the SAQ
        renderManager.IASetInputLayoutDX11(g_pVertexLayout2);
        renderManager.RSSetStateDX11(g_Rasterizer2);
        renderManager.IASetVertexBuffersDX11(0, 1, &g_pVertexBuffer2->getyBufferDX11(), &stride, &offset);
        renderManager.IASetIndexBufferDX11(g_pIndexBuffer2->getyBufferDX11(), DXGI_FORMAT_R16_UINT, 0);
        renderManager.VSSetShaderDX11(g_pVertexShader2, NULL, 0);
        renderManager.PSSetShaderDX11(g_pPixelShader2, NULL, 0);
        //g_pImmediateContext->DrawIndexed(6, 0, 0);


        //
        // Present our back buffer to our front buffer
        //

        //UIRender();
#endif
    }

    void test::CleanupDevice()
    {
#if defined(DX11)
        if (renderManager.getDeviceContextDX11()) renderManager.getDeviceContextDX11()->ClearState();

        if (g_pSamplerLinear) g_pSamplerLinear->Release();
        if (ResorceView1) ResorceView1->Release();

        if (g_pCBNeverChanges->getyBufferDX11()) g_pCBNeverChanges->ReleaseDX11();
        if (g_pCBChangeOnResize->getyBufferDX11()) g_pCBChangeOnResize->ReleaseDX11();
        if (g_pCBChangesEveryFrame->getyBufferDX11()) g_pCBChangesEveryFrame->ReleaseDX11();
        if (g_pVertexBuffer->getyBufferDX11()) g_pVertexBuffer->ReleaseDX11();
        if (g_pIndexBuffer->getyBufferDX11()) g_pIndexBuffer->ReleaseDX11();

        if (g_pVertexLayout) g_pVertexLayout->Release();
        if (g_pVertexShader) g_pVertexShader->Release();
        if (g_pPixelShader) g_pPixelShader->Release();

        if (Texture->getTextureDX11()) Texture->ReleaseDX11();

        if (g_pDepthStencilView->getyDepthStencilViewDX11()) g_pDepthStencilView->getyDepthStencilViewDX11()->Release();
        if (RenderTargetView1->getRenderTargetViewDX11()) RenderTargetView1->getRenderTargetViewDX11()->Release();
        if (renderManager.getSwapChainDX11()) renderManager.getSwapChainDX11()->Release();
        if (renderManager.getDeviceContextDX11()) renderManager.getDeviceContextDX11()->Release();
        if (renderManager.getDeviceDX11()) renderManager.getDeviceDX11()->Release();
#endif
    }


    extern test& GetTestObj(HWND _hwnd)
    {
        static test* pTest = nullptr;
        if (pTest == nullptr)
        {
            pTest = new test();
            pTest->InitDevice(_hwnd);
        }
        return *pTest;
    }
}