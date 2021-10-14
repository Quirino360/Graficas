#include "test.h"
#include "TechniqueS.h"

namespace GraphicsModule
{
#if defined(DX11)
    void test::InitVariables()
    {
#if defined(DX11)
        Texture = new Texture2D();

        g_pVertexBuffer = new Buffer();
        g_pIndexBuffer = new Buffer();
        g_pCBNeverChanges = new Buffer();
        g_pCBChangeOnResize = new Buffer();
        g_pCBChangesEveryFrame = new Buffer();

        g_DirLightBuffer = new Buffer();
        g_PointLightBuffer = new Buffer();
        g_SpotLightBuffer = new Buffer();
        g_AmbientLightBuffer = new Buffer();
        g_SpecularBuffer = new Buffer();
        g_ShiniesBuffer = new Buffer();
        g_DiffuseBuffer = new Buffer();
            
        
        RenderTargetV = new RenderTargetView();
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
        hr = renderManager.CreateRenderTargetViewDX11(pBackBuffer->getTextureDX11(), NULL, &RenderTargetV->getRenderTargetViewDX11());
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

        /*// and the resource view for the shader
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1; // same as orig texture
        hr = renderManager.CreateShaderResourceViewDX11(Texture->getTextureDX11(), &srvDesc, &ShaderResourceView);
        if (FAILED(hr))
            return hr;*/

        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetV->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());

        //Set the viewport
        VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;

        renderManager.RSSetViewportsDX11(1, reinterpret_cast<D3D11_VIEWPORT*>(&vp));

        
        m_effect.CreateAllTechniques();
        m_effect.CreatePass();
        m_effect.SetActiveTechnique(NORMAL_TECHNIQUES::PIXEL_SHADER, SPECULAR_TECHNIQUES::BLINN_PHONG, TEXTURE_MAP_NORMAL);
        /**/

        // Set primitive topology
        renderManager.IASetPrimitiveTopologyDX11(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // ------------------------- Create the constant buffers ------------------------- //
        BUFFER_DESC_DX11 bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DEFAULT_DX11;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = 0;

        // Create CBNeverChanges (b0)
        bd.ByteWidth = sizeof(cbNeverChanges);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBNeverChanges->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create CBChangeOnResize (b1)
        bd.ByteWidth = sizeof(cbChangeOnResize);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBChangeOnResize->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create CBChangesEveryFrame (b2)
        bd.ByteWidth = sizeof(CBChangesEveryFrame);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_pCBChangesEveryFrame->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create dir light buffer (b3)
        bd.ByteWidth = sizeof(DirLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_DirLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create point light buffer (b4)
        bd.ByteWidth = sizeof(PointLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_PointLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create spot light buffer (b5)
        bd.ByteWidth = sizeof(spotLight);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_SpotLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create ambient light buffer (b6)
        bd.ByteWidth = sizeof(Ambient);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_AmbientLightBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create Specular buffer (b7)
        bd.ByteWidth = sizeof(Specular);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_SpecularBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create Shinies buffer (b8)
        bd.ByteWidth = sizeof(Shinies);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_ShiniesBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Create Diffuse buffer (b9)
        bd.ByteWidth = sizeof(Diffuse);
        hr = renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &g_DiffuseBuffer->getyBufferDX11());
        if (FAILED(hr))
            return hr;

        // Load the Textures
        std::string textureString = "ZResorces//meshes//Gun//Textures//base_albedo.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), textureString.c_str(), NULL, NULL, &ResourceViewAlbedo, NULL); // t0
        if (FAILED(hr))
            return hr;

        textureString = "ZResorces//meshes//Gun//Textures//base_normal.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), textureString.c_str(), NULL, NULL, &ResourceViewNormal, NULL); // t1
        if (FAILED(hr))
            return hr;

        textureString = "ZResorces//meshes//Gun//Textures//base_AO.jpg";
        hr = D3DX11CreateShaderResourceViewFromFile(renderManager.getDeviceDX11(), textureString.c_str(), NULL, NULL, &ResourceViewSpecular, NULL); // t2
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

        hr = renderManager.CreateSamplerStateDX11(&sampDesc, &sampnormalMap);
        if (FAILED(hr))
            return hr;

        hr = renderManager.CreateSamplerStateDX11(&sampDesc, &samplerSpecular);
        if (FAILED(hr))
            return hr;/**/

        // Initialize the world matrices
        mesh.Init();

        // Initialize the view matrix
        camera.setEye(0.0f, 3.0f, -6.0f);
        camera.setAt(0.0f, 1.0f, 0.0f);
        camera.setUp(0.0f, 1.0f, 0.0f);
        camera.setViewMatrix();

        g_View = XMMATRIX(camera.getViewMatrix().matrix4);


        cbNeverChanges cbNeverChanges;
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

        m_SpecularBuffer.n2 = XMFLOAT3(1.0f, 1.0f, 1.0f);
        m_SpecularBuffer.kSpecular = FLOAT(1.0f);
        renderManager.UpdateSubresourceDX11(g_SpecularBuffer->getyBufferDX11(), 0, NULL, &m_SpecularBuffer, 0, 0);


        m_ShiniesBuffer.n3 = XMFLOAT3(1.0f, 1.0f, 1.0f);
        m_ShiniesBuffer.shininess = (60.0f);
        renderManager.UpdateSubresourceDX11(g_ShiniesBuffer->getyBufferDX11(), 0, NULL, &m_ShiniesBuffer, 0, 0);

        m_DiffuseBuffer.n4 = XMFLOAT3(1.0f, 1.0f, 1.0f);
        m_DiffuseBuffer.kDiffuse = FLOAT(1.0f);
        renderManager.UpdateSubresourceDX11(g_ShiniesBuffer->getyBufferDX11(), 0, NULL, &m_DiffuseBuffer, 0, 0);


#elif defined(OGL)

// configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    //Shader aux("Shader1.fx", "Shader2.fx");

    ourShader.CreateShader("Shader1.fx", "Shader2.fx");

    //std::string fName = OpenFileGetName(g_hwnd);
    //testOBj.aLoadModel.loadModel(fName);
    aLoadModel.loadModel("ZResorces/meshes/Gun/drakefire_pistol_low.obj");
    // set up vertex data (and buffer(s)) and configure vertex attributes

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
    fif = FreeImage_GetFileType("Ahegao2k.jpg", 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename("Ahegao2k.jpg");
    if (fif == FIF_UNKNOWN)
        return S_FALSE;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
    {
        dib = FreeImage_Load(fif, "Ahegao2k.jpg");
        dib = FreeImage_ConvertTo32Bits(dib);
    }
    if (!dib)
        return S_FALSE;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return S_FALSE;
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
        return S_FALSE;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif2))
    {
        dib2 = FreeImage_Load(fif2, "Black.jpg");
        dib2 = FreeImage_ConvertTo32Bits(dib2);
    }

    //if the image failed to load, return failure
    if (!dib2)
        return S_FALSE;

    //retrieve the image data
    bits2 = FreeImage_GetBits(dib2);
    //get the image width and height
    width2 = FreeImage_GetWidth(dib2);
    height2 = FreeImage_GetHeight(dib2);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits2 == 0) || (width2 == 0) || (height2 == 0))
        return S_FALSE;
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
        //static float t = 0.0f;
        if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
        {
            t += (float)XM_PI * 0.0125f;
        }
        else
        {
            static DWORD dwTimeStart = 0;
            DWORD dwTimeCur = GetTickCount64();
            if (dwTimeStart == 0)
                dwTimeStart = dwTimeCur;
            t = (dwTimeCur - dwTimeStart) / 1000.0f;
        }

        mesh.Update(renderManager, g_pCBChangesEveryFrame); //a mesh

        renderManager.UpdateSubresourceDX11(g_DirLightBuffer->getyBufferDX11(), 0, NULL, &m_DirLightBuffer, 0, 0); // dir light
        renderManager.UpdateSubresourceDX11(g_PointLightBuffer->getyBufferDX11(), 0, NULL, &m_PointLightBuffer, 0, 0); // point light
        renderManager.UpdateSubresourceDX11(g_SpotLightBuffer->getyBufferDX11(), 0, NULL, &m_SpotLightBuffer, 0, 0); // spot light
        renderManager.UpdateSubresourceDX11(g_AmbientLightBuffer->getyBufferDX11(), 0, NULL, &m_AmbientLightBuffer, 0, 0); // ambient light
        renderManager.UpdateSubresourceDX11(g_SpecularBuffer->getyBufferDX11(), 0, NULL, &m_SpecularBuffer, 0, 0); // specular
        renderManager.UpdateSubresourceDX11(g_ShiniesBuffer->getyBufferDX11(), 0, NULL, &m_ShiniesBuffer, 0, 0); // shinines
        renderManager.UpdateSubresourceDX11(g_DiffuseBuffer->getyBufferDX11(), 0, NULL, &m_DiffuseBuffer, 0, 0); // diffuse

        // ------------------------------ mouse shit ----------------------------------------- //
        *oldCursor = *newCursor;
        GetCursorPos(newCursor);
        camera.RotateCamera(Vector3(newCursor->x, newCursor->y, 0), Vector3(oldCursor->x, oldCursor->y, 0));

        if (true == mouseMove)
        {
            cbNeverChanges cbNeverChanges;
            cbNeverChanges.mView = XMMatrixTranspose(g_View);
            renderManager.UpdateSubresourceDX11(g_pCBNeverChanges->getyBufferDX11(), 0, NULL, &cbNeverChanges, 0, 0);

            cbChangeOnResize cbChangesOnResize;
            cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
            renderManager.UpdateSubresourceDX11(g_pCBChangeOnResize->getyBufferDX11(), 0, NULL, &cbChangesOnResize, 0, 0);

            // Move the mouse updating the position
            g_View = XMMATRIX(camera.getViewMatrix().matrix4);
            cbNeverChanges.mView = XMMatrixTranspose(g_View);
            renderManager.UpdateSubresourceDX11(g_pCBNeverChanges->getyBufferDX11(), 0, NULL, &cbNeverChanges, 0, 0);
        }

#elif defined (OGL)
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
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
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
        
        UINT stride = sizeof(Vertex);
        UINT offset = 0;

        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha


        //print a mesh
        renderManager.ClearRenderTargetViewDX11(RenderTargetV->getRenderTargetViewDX11(), ClearColor);
        renderManager.ClearDepthStencilViewDX11(g_pDepthStencilView->getyDepthStencilViewDX11(), D3D11_CLEAR_DEPTH, 1.0f, 0);
        renderManager.OMSetRenderTargetsDX11(1, &RenderTargetV->getRenderTargetViewDX11(), g_pDepthStencilView->getyDepthStencilViewDX11());

        renderManager.PSSetShaderResourcesDX11(0, 1, &ResourceViewAlbedo); // t0
        renderManager.PSSetShaderResourcesDX11(1, 1, &ResourceViewNormal); // t1
        renderManager.PSSetShaderResourcesDX11(2, 1, &ResourceViewSpecular); // t2
        /**/
        
        //renderManager.IASetInputLayoutDX11(shader.g_pVertexLayout);
        renderManager.IASetInputLayoutDX11(m_effect.GetShader().g_pVertexLayout);
        renderManager.RSSetStateDX11(g_Rasterizer);

        renderManager.IASetVertexBuffersDX11(0, 1, &g_pVertexBuffer->getyBufferDX11(), &stride, &offset);//
        renderManager.IASetIndexBufferDX11(g_pIndexBuffer->getyBufferDX11(), DXGI_FORMAT_R16_UINT, 0);//

        // -------------------- Vertex shader -------------------- //
        //renderManager.VSSetShaderDX11(shader.g_pVertexShader, NULL, 0); //vertex shader
        renderManager.VSSetShaderDX11(m_effect.GetShader().g_pVertexShader, NULL, 0); //vertex shader
        renderManager.VSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.VSSetConstantBuffersDX11(3, 1, &g_DirLightBuffer->getyBufferDX11()); // vsset dir light
        renderManager.VSSetConstantBuffersDX11(4, 1, &g_PointLightBuffer->getyBufferDX11()); // vsset point light
        renderManager.VSSetConstantBuffersDX11(5, 1, &g_SpotLightBuffer->getyBufferDX11()); // vsset spot light
        renderManager.VSSetConstantBuffersDX11(6, 1, &g_AmbientLightBuffer->getyBufferDX11()); // vsset ambient light
        renderManager.VSSetConstantBuffersDX11(7, 1, &g_SpecularBuffer->getyBufferDX11()); // vsset specular
        renderManager.VSSetConstantBuffersDX11(8, 1, &g_ShiniesBuffer->getyBufferDX11()); // vsset shinines
        renderManager.VSSetConstantBuffersDX11(9, 1, &g_DiffuseBuffer->getyBufferDX11()); // vsset diffuse


        // -------------------- Pixel shader -------------------- //
        //renderManager.PSSetShaderDX11(shader.g_pPixelShader, NULL, 0); //pixel shader
        renderManager.PSSetShaderDX11(m_effect.GetShader().g_pPixelShader, NULL, 0); //pixel shader
        renderManager.PSSetConstantBuffersDX11(0, 1, &g_pCBNeverChanges->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(1, 1, &g_pCBChangeOnResize->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(2, 1, &g_pCBChangesEveryFrame->getyBufferDX11());
        renderManager.PSSetConstantBuffersDX11(3, 1, &g_DirLightBuffer->getyBufferDX11()); //vsset dirlight
        renderManager.PSSetConstantBuffersDX11(4, 1, &g_PointLightBuffer->getyBufferDX11()); // vsset point light
        renderManager.PSSetConstantBuffersDX11(5, 1, &g_SpotLightBuffer->getyBufferDX11()); // vsset spot light
        renderManager.PSSetConstantBuffersDX11(6, 1, &g_AmbientLightBuffer->getyBufferDX11()); // vsset ambient light
        renderManager.PSSetConstantBuffersDX11(7, 1, &g_SpecularBuffer->getyBufferDX11()); // vsset specular
        renderManager.PSSetConstantBuffersDX11(8, 1, &g_ShiniesBuffer->getyBufferDX11()); // vsset shinines
        renderManager.PSSetConstantBuffersDX11(9, 1, &g_DiffuseBuffer->getyBufferDX11()); // vsset diffuse

        renderManager.PSSetSamplersDX11(0, 1, &g_pSamplerLinear); // s0
        renderManager.PSSetSamplersDX11(1, 1, &sampnormalMap); // s1
        renderManager.PSSetSamplersDX11(2, 1, &samplerSpecular); // s2 /**/



        renderManager.DrawIndexedDX11(aLoadModel.numIndices, 0, 0);

#elif defined(OGL)
        // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, aLoadModel.numVertex);
#endif
    }

    void test::CleanupDevice()
    {
#if defined(DX11)
        if (renderManager.getDeviceContextDX11()) renderManager.getDeviceContextDX11()->ClearState();

        if (g_pSamplerLinear) g_pSamplerLinear->Release();
        if (sampnormalMap) sampnormalMap->Release();
        if (samplerSpecular) samplerSpecular->Release();

        if (ResourceViewAlbedo) ResourceViewAlbedo->Release();
        if (ResourceViewNormal) ResourceViewNormal->Release();
        if (ResourceViewSpecular) ResourceViewSpecular->Release();


        if (g_pCBNeverChanges->getyBufferDX11()) g_pCBNeverChanges->ReleaseDX11();
        if (g_pCBChangeOnResize->getyBufferDX11()) g_pCBChangeOnResize->ReleaseDX11();
        if (g_pCBChangesEveryFrame->getyBufferDX11()) g_pCBChangesEveryFrame->ReleaseDX11();
        if (g_DirLightBuffer->getyBufferDX11()) g_DirLightBuffer->ReleaseDX11(); //release dir light
        if (g_PointLightBuffer->getyBufferDX11()) g_PointLightBuffer->ReleaseDX11(); //release point light
        if (g_SpotLightBuffer->getyBufferDX11()) g_SpotLightBuffer->ReleaseDX11(); //release spot light
        if (g_AmbientLightBuffer->getyBufferDX11()) g_AmbientLightBuffer->ReleaseDX11(); //release ambient light
        if (g_SpecularBuffer->getyBufferDX11()) g_SpecularBuffer->ReleaseDX11(); //release specular
        if (g_ShiniesBuffer->getyBufferDX11()) g_ShiniesBuffer->ReleaseDX11(); //release dshinines
        if (g_DiffuseBuffer->getyBufferDX11()) g_DiffuseBuffer->ReleaseDX11(); //release diffuse


        if (g_pVertexBuffer->getyBufferDX11()) g_pVertexBuffer->ReleaseDX11();
        if (g_pIndexBuffer->getyBufferDX11()) g_pIndexBuffer->ReleaseDX11();

        if (Texture->getTextureDX11()) Texture->ReleaseDX11();

        if (g_pDepthStencilView->getyDepthStencilViewDX11()) g_pDepthStencilView->getyDepthStencilViewDX11()->Release();
        if (RenderTargetV->getRenderTargetViewDX11()) RenderTargetV->getRenderTargetViewDX11()->Release();
        if (renderManager.getSwapChainDX11()) renderManager.getSwapChainDX11()->Release();
        if (renderManager.getDeviceContextDX11()) renderManager.getDeviceContextDX11()->Release();
        if (renderManager.getDeviceDX11()) renderManager.getDeviceDX11()->Release();

#elif defined(OGL)

        // optional: de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

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