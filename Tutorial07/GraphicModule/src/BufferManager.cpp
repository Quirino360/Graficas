#include "BufferManager.h"
#include "test.h"

// Editor Manager

void BufferManager::Update()
{
    for (unsigned int i = 0; i < m_matrix.size(); i++)
    {
        // Una iterfz de todos los iobjetos
        // Usar lo que ya tenemos dandole un sentido 
        // El editor va utilizar elementos de lo que ya cva estar con una interfaz
        // No necesito un director de musica para todo

    }

    for (unsigned int i = 0; i < m_floats4.size(); i++)
    {

    }
    
}

void BufferManager::Render()
{
}

BufferManager::BufferManager()
{
}
BufferManager::~BufferManager()
{
}

bool BufferManager::CreateMatrix4x4(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bMatrix aux;
    aux.name = _bufferName;
    m_matrix.push_back(aux);

    // -----
    HRESULT hr = S_OK;
    BUFFER_DESC_DX11 bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT_DX11;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;


    bd.ByteWidth = sizeof(XMMATRIX);
    if (FAILED(testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &m_matrix[m_matrix.size() - 1].buffer.getyBufferDX11())))
        return false;
    return true;
}

bool BufferManager::CreateFloat4(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bFloat4 aux;
    aux.name = _bufferName;
    m_floats4.push_back(aux);

    // -----
    HRESULT hr = S_OK;
    BUFFER_DESC_DX11 bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT_DX11;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    bd.ByteWidth = sizeof(float4);
    if (FAILED(testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &m_floats4[m_floats4.size() - 1].buffer.getyBufferDX11())))
        return false;
    return true;
}

bool BufferManager::CreateFloat3(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bFloat3 aux;
    aux.name = _bufferName;
    m_floats3.push_back(aux);

    // -----
    HRESULT hr = S_OK;
    BUFFER_DESC_DX11 bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT_DX11;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    bd.ByteWidth = sizeof(float3);
    if (FAILED(testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &m_floats3[m_floats3.size() - 1].buffer.getyBufferDX11())))
        return false;
    return true;
}

bool BufferManager::CreateFloat2(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bFloat2 aux;
    aux.name = _bufferName;
    m_floats2.push_back(aux);

    // -----
    HRESULT hr = S_OK;
    BUFFER_DESC_DX11 bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT_DX11;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    bd.ByteWidth = sizeof(float2);
    if (FAILED(testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &m_floats2[m_floats2.size() - 1].buffer.getyBufferDX11())))
        return false;
    return true;
}

bool BufferManager::CreateFloat(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bFloat aux;
    aux.name = _bufferName;
    m_floats.push_back(aux);

    // -----
    HRESULT hr = S_OK;
    BUFFER_DESC_DX11 bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT_DX11;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;


    bd.ByteWidth = sizeof(float);
    if (FAILED(testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), NULL, &m_floats[m_floats.size() - 1].buffer.getyBufferDX11())))
        return false;
    return true;
}

bool BufferManager::CreateInt4(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateInt3(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateInt(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateInt1(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateBool(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateResourceView(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
    return true;
}

bool BufferManager::CreateSampler(std::string _bufferName)
{
    auto& testOBj = GetTestObj();
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

    if (FAILED(testOBj.renderManager.CreateSamplerStateDX11(&sampDesc, &m_Samplers[m_Samplers.size() - 1].values)))
        return false;
    return true;
}

bool BufferManager::CreateRenderTargetView(std::string _bufferName)
{
    auto& testOBj = GetTestObj();

    // -----
    bRenderTarget aux;
    aux.name = _bufferName;
    m_renderTargetsView.push_back(aux);

    // ---------- Create a render target view 
    HRESULT hr = S_OK;

    // ----- Create texture
    Texture2D* pBackBuffer = new Texture2D();
    hr = testOBj.renderManager.GetBufferDX11(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer->getTextureDX11());
    if (FAILED(hr))
        return false;
    return true;

    // Create Render Target View
    hr = testOBj.renderManager.CreateRenderTargetViewDX11(pBackBuffer->getTextureDX11(), NULL, &m_renderTargetsView[m_renderTargetsView.size() - 1].values.getRenderTargetViewDX11());
    pBackBuffer->getTextureDX11()->Release();
    if (FAILED(hr))
        return false;
    return true;
}