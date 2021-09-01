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
#if defined(DX11)


        Texture = new Texture2D();

        g_pVertexBuffer = new Buffer();
        g_pIndexBuffer = new Buffer();
        g_pCBNeverChanges = new Buffer();
        g_pCBChangeOnResize = new Buffer();
        g_pCBChangesEveryFrame = new Buffer();
        g_pVertexBuffer2 = new Buffer();
        g_pIndexBuffer2 = new Buffer();
        g_DirLightBuffer = new Buffer();

        RenderTargetView1 = new RenderTargetView();
        //RenderTargetView2 = new RenderTargetView();
        //RenderTargetView3 = new RenderTargetView();
        //RenderTargetView4 = new RenderTargetView();
        g_pDepthStencilView = new DepthStencilView();

#endif 
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

<<<<<<< HEAD


        /*// and the resource view for the shader
=======
        // and the resource view for the shader
>>>>>>> parent of 89f9bc6 (Parcial 1)
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1; // same as orig texture
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &srvDesc, &ShaderResourceView);
        if (FAILED(hr))
            return hr;

<<<<<<< HEAD
        renderManager.OMSetRenderTargetsDX11(4, &RenderTargetV->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());
=======
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView1->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());
>>>>>>> parent of 89f9bc6 (Parcial 1)

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
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }

<<<<<<< HEAD
        // Create dir light buffer (b4)
        bd.ByteWidth = sizeof(DirLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_DirLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create point light buffer (b5)
        bd.ByteWidth = sizeof(PointLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_PointLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create spot light buffer (b6)
        bd.ByteWidth = sizeof(spotLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_SpotLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create ambient light buffer (b7)
        bd.ByteWidth = sizeof(Ambient);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_AmbientLightBuffer->getyBufferDX11());
=======

        };
        UINT numElements = ARRAYSIZE(layout);

        // Create the input layout
        hr = renderManager.CreateInputLayoutDX11(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return hr;


        // Compile the pixel shader
        ID3DBlob* pPSBlob = NULL;
        hr = CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
>>>>>>> parent of 89f9bc6 (Parcial 1)
        if (FAILED(hr))
        {
            MessageBox(NULL,
                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
            return hr;
        }

<<<<<<< HEAD
        // Create Specular buffer (b8)
        bd.ByteWidth = sizeof(Specular);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_SpecularBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create Shinies buffer (b9)
        bd.ByteWidth = sizeof(Shinies);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_ShiniesBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create Diffuse buffer (b10)
        bd.ByteWidth = sizeof(Diffuse);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_DiffuseBuffer->getyBufferDX11());
=======
        // Create the pixel shader
        hr = renderManager.CreatePixelShaderDX11(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;

        //if want to set vertex and indices ists here 

        // Set primitive topology
        renderManager.IASetPrimitiveTopologyDX11(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        BUFFER_DESC_DX11 bd;
        ZeroMemory(&bd, sizeof(bd));

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
>>>>>>> parent of 89f9bc6 (Parcial 1)
        if (FAILED(hr))
            return hr;

        bd.ByteWidth = sizeof(CBChangesEveryFrame);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBChangesEveryFrame->getyBufferDX11());
        if (FAILED(hr))
            return hr;

<<<<<<< HEAD
        textureString = "ZResorces//meshes//Gun//Textures//base_normal.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), textureString.c_str(), NULL, NULL, &ResourceViewNormal, NULL); // t2
        if (FAILED(hr))
            return hr;

        textureString = "ZResorces//meshes//Gun//Textures//base_metallic.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), textureString.c_str(), NULL, NULL, &ResourceViewSpecular, NULL); // t3
=======

        bd.ByteWidth = sizeof(DirLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_DirLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;


        // Load the Texture

        std::string pepe = "Ahegao2k.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(),pepe.c_str() , NULL, NULL, &ResorceView1, NULL);
>>>>>>> parent of 89f9bc6 (Parcial 1)
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


#elif defined(OGL)
    // -------------------- Shaders -------------------- //
// configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    //ourShader.Init("Shader1.fx", "Shader2.fx");
    

    AssimpLoadModel aLoadModel;
    //std::string fName = OpenFileGetName(g_hwnd);
    //testOBj.aLoadModel.loadModel(fName);

<<<<<<< HEAD
    if (nullptr == aLoadModel.indices)
    {
        //aLoadModel.loadModel("ZResorces/meshes/Gun/drakefire_pistol_low.obj");
        aLoadModel.loadModel("ZResorces/meshes/Guard/boblampclean.md5mesh");
    }

    // -------------------- Mesh -------------------- //
    // set up vertex data (and buffer(s)) and configure vertex attributes
=======
    
>>>>>>> parent of 89f9bc6 (Parcial 1)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, aLoadModel.numVertex * sizeof(Vertex), &aLoadModel.vertices[0], GL_STATIC_DRAW);
    
    // position attribute
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // texture coord attribute
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);


<<<<<<< HEAD
    // -------------------- Texture -------------------- //
=======
>>>>>>> parent of 89f9bc6 (Parcial 1)
    // load and create a texture 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; //image format
    FIBITMAP* dib(0);     //pointer to the image, once loaded
    BYTE* bits(0); //pointer to the image data


    //check the file signature and deduce its format
    //fif = FreeImage_GetFileType("Ahegao2k.jpg", 0);
    fif = FreeImage_GetFileType("ZResorces/meshes/Guard/Textures/guard1_face.tga");

    if (fif == FIF_UNKNOWN)
    {
        //fif = FreeImage_GetFIFFromFilename("Ahegao2k.jpg");
        fif = FreeImage_GetFIFFromFilename("ZResorces/meshes/Guard/Textures/guard1_face.tga");
    }
    if (fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
    {
        //dib = FreeImage_Load(fif, "Ahegao2k.jpg");
        dib = FreeImage_Load(fif, "ZResorces/meshes/Guard/Textures/guard1_face.tga");
        dib = FreeImage_ConvertTo32Bits(dib);
    }
    if (!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return false;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //OpenGL's image ID to map to
    GLuint gl_texID;
    //generate an OpenGL texture ID for this texture    
    glGenTextures(1, &gl_texID);
    //store the texture ID mapping
    texture = gl_texID;
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
    glGenerateMipmap(GL_TEXTURE_2D);

    FreeImage_Unload(dib);
    
    // load and create a texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width2, height2, nrChannels2;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
      //image format
    FREE_IMAGE_FORMAT fif2 = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP* dib2(0);
    //pointer to the image data
    BYTE* bits2(0);
    //image width and height
    //unsigned int width(0), height(0);

    //check the file signature and deduce its format
    fif2 = FreeImage_GetFileType("Black.jpg", 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif2 == FIF_UNKNOWN)
        fif2 = FreeImage_GetFIFFromFilename("Black.jpg");
    //if still unkown, return failure
    if (fif2 == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif2))
    {
        dib2 = FreeImage_Load(fif2, "Black.jpg");
        dib2 = FreeImage_ConvertTo32Bits(dib2);
    }

    //if the image failed to load, return failure
    if (!dib2)
        return false;

    //retrieve the image data
    bits2 = FreeImage_GetBits(dib2);
    //get the image width and height
    width2 = FreeImage_GetWidth(dib2);
    height2 = FreeImage_GetHeight(dib2);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits2 == 0) || (width2 == 0) || (height2 == 0))
        return false;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //OpenGL's image ID to map to
    GLuint gl_texID2;
    //generate an OpenGL texture ID for this texture    
    glGenTextures(1, &gl_texID2);
    //store the texture ID mapping
    texture2 = gl_texID2;
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, gl_texID2);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits2);
    glGenerateMipmap(GL_TEXTURE_2D);

    FreeImage_Unload(dib2);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);



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


        /*m_DirLightBuffer.dir.x = 0.0f;
        m_DirLightBuffer.dir.y = -1.0f;
        m_DirLightBuffer.dir.z = 1.0f;
        m_DirLightBuffer.dir.w = 0.0f;*/
        renderManager.UpdateSubresourceDX11(g_DirLightBuffer->getyBufferDX11(), 0, NULL, &m_DirLightBuffer, 0, 0);//dir light


        *oldCursor = *newCursor;
        GetCursorPos(newCursor);
        camera.RotateCamera(Vector3(newCursor->x, newCursor->y, 0), Vector3(oldCursor->x, oldCursor->y, 0));


        // Modify the color
        g_vMeshColor.x = 0.75;
        g_vMeshColor.y = 0.75;
        g_vMeshColor.z = 0.75;

        // ------------------------------ mouse shit ----------------------------------------- //
        if (true == mouseMove)
        {
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
        }

#elif defined (OGL)

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        //-------------------------------- Projection Matrix -----------------------------------//
        // create transformations
        glm::mat4 model = glm::mat4(1.0f); //initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::rotate(model, 180.0f, glm::vec3(0.0f, 180.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::translate(view, glm::vec3(0.0f, -30.0f, -100.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)1080 / (float)720, 0.1f, 100.0f);

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");


        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        ourShader.setMat4("projection", projection); //Projection Matrix






#endif
    }

    void test::Render()
    {
#if defined(DX11)

        //g_World = XMMatrixRotationY(t);

        UINT stride = sizeof(SimpleVertex);
        UINT offset = 0;

        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
        CBChangesEveryFrame cb;


        // ----------------------------------------------- Print an object ---------------------------------------------------------//
        renderManager.ClearRenderTargetViewDX11(RenderTargetView1->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetView1->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());


        renderManager.PSSetShaderResourcesDX11(0, 1, &ResorceView1); 
        g_World = XMMatrixTranslation(0, 0, 0);
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        renderManager.UpdateSubresourceDX11(g_pCBChangesEveryFrame->getyBufferDX11(), 0, NULL, &cb, 0, 0);


<<<<<<< HEAD
        renderManager.PSSetShaderResourcesDX11(0, 1, &ResourceViewAlbedo); // t0
        renderManager.PSSetShaderResourcesDX11(2, 1, &ResourceViewNormal); // t2
        renderManager.PSSetShaderResourcesDX11(1, 1, &ResourceViewSpecular); // t3
        /**/
=======
>>>>>>> parent of 89f9bc6 (Parcial 1)
        
        // Set the input layout
        renderManager.IASetInputLayoutDX11(g_pVertexLayout);
        renderManager.RSSetStateDX11(g_Rasterizer);

        renderManager.IASetVertexBuffersDX11(0, 1, &g_pVertexBuffer->getyBufferDX11(), &stride, &offset);//
        renderManager.IASetIndexBufferDX11(g_pIndexBuffer->getyBufferDX11(), DXGI_FORMAT_R16_UINT, 0);//
        renderManager.VSSetShaderDX11(g_pVertexShader, NULL, 0);//

<<<<<<< HEAD
        // -------------------- Vertex shader -------------------- //
        renderManager.VSSetShaderDX11(m_effect.GetShader().g_pVertexShader, NULL, 0); //vertex shader
        renderManager.VSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());


        // -------------------- Pixel shader -------------------- //
        renderManager.PSSetShaderDX11(m_effect.GetShader().g_pPixelShader, NULL, 0); //pixel shader
        /*renderManager.PSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(4, 1, &g_DirLightBuffer->getyBufferDX11()); //vsset dirlight
        renderManager.PSSetConstantBuffersDX11(5, 1, &g_PointLightBuffer->getyBufferDX11()); // vsset point light
        renderManager.PSSetConstantBuffersDX11(6, 1, &g_SpotLightBuffer->getyBufferDX11()); // vsset spot light
        renderManager.PSSetConstantBuffersDX11(7, 1, &g_AmbientLightBuffer->getyBufferDX11()); // vsset ambient light
        renderManager.PSSetConstantBuffersDX11(8, 1, &g_SpecularBuffer->getyBufferDX11()); // vsset specular
        renderManager.PSSetConstantBuffersDX11(9, 1, &g_ShiniesBuffer->getyBufferDX11()); // vsset shinines
        renderManager.PSSetConstantBuffersDX11(10, 1, &g_DiffuseBuffer->getyBufferDX11()); // vsset diffuse/**/

        renderManager.PSSetSamplersDX11(0, 1, &g_pSamplerLinear); // s0
        renderManager.PSSetSamplersDX11(2, 1, &sampnormalMap); // s2
        renderManager.PSSetSamplersDX11(3, 1, &samplerSpecular); // s3 /**/

=======
        renderManager.VSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(3, 1, &g_DirLightBuffer->getyBufferDX11()); //vsset dirlight
>>>>>>> parent of 89f9bc6 (Parcial 1)


        renderManager.PSSetShaderDX11(g_pPixelShader, NULL, 0);//
        renderManager.PSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.PSSetSamplersDX11(0, 1, &g_pSamplerLinear);
        //renderManager.DrawIndexedDX11(36, 0, 0);
        renderManager.DrawIndexedDX11(aLoadModel.numIndices, 0, 0);


        //UIRender();
#elif defined(OGL)

        // render box
        aLoadModel.Render();
        /*glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, aLoadModel.numVertex);/**/
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
        if (g_DirLightBuffer->getyBufferDX11()) g_DirLightBuffer->ReleaseDX11(); //release dir light


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

#elif defined(OGL)

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

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




/*
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


                /*
        // Render the SAQ
        renderManager.IASetInputLayoutDX11(g_pVertexLayout2);
        renderManager.RSSetStateDX11(g_Rasterizer2);
        renderManager.IASetVertexBuffersDX11(0, 1, &g_pVertexBuffer->getyBufferDX11(), &stride, &offset);
        renderManager.IASetIndexBufferDX11(g_pIndexBuffer2->getyBufferDX11(), DXGI_FORMAT_R16_UINT, 0);
        renderManager.VSSetShaderDX11(g_pVertexShader, NULL, 0);
        renderManager.PSSetShaderDX11(g_pPixelShader, NULL, 0);
        //g_pImmediateContext->DrawIndexed(6, 0, 0);*/


        // -----------------------------------------------------------------------------------------------------------------------------------------------------------/ 
        // ---------------------------------------------- set render target View, Shader ResourceView, and Texture ---------------------------------------------------/ 

        // ----------------------------------------------------------  texture 2 ---------------------------------------------------------- //
        /*
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
            /**/