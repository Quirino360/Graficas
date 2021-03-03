#include "Device.h"

Device::Device()
{
    g_pd3dDevice = nullptr;
}

Device::~Device()
{
    if (nullptr != g_pd3dDevice)
    {
        delete g_pd3dDevice;
        g_pd3dDevice = nullptr;
    }
}

HRESULT Device::CopyD3D11CreateDeviceAndSwapChain(IDXGIAdapter* _pAdapter, D3D_DRIVER_TYPE _DriverType, HMODULE _Software, UINT _Flags, const D3D_FEATURE_LEVEL* _pFeatureLevels, UINT _FeatureLevels, UINT _SDKVersion, const DXGI_SWAP_CHAIN_DESC* _pSwapChainDesc, IDXGISwapChain** _ppSwapChain, ID3D11Device** _ppDevice, D3D_FEATURE_LEVEL* _pFeatureLevel, ID3D11DeviceContext** _ppImmediateContext)
{
    return  D3D11CreateDeviceAndSwapChain(_pAdapter, _DriverType, _Software, _Flags, _pFeatureLevels, _FeatureLevels, _SDKVersion, _pSwapChainDesc, _ppSwapChain, _ppDevice, _pFeatureLevel, _ppImmediateContext);
}

HRESULT Device::CopyCreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView)
{
    return g_pd3dDevice->CreateRenderTargetView(_pResource, _pDesc, _ppRTView);
}

HRESULT Device::CopyCreateTexture2D(const D3D11_TEXTURE2D_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Texture2D** _ppTexture2D)
{
    return g_pd3dDevice->CreateTexture2D(_pDesc, _pInitialData, _ppTexture2D);
}

HRESULT Device::CopyCreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDepthStencilView)
{
    return g_pd3dDevice->CreateDepthStencilView(_pResource, _pDesc, _ppDepthStencilView);
}

HRESULT Device::CopyCreateVertexShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11VertexShader** _ppVertexShader)
{
    return g_pd3dDevice->CreateVertexShader(_pShaderBytecode, _BytecodeLength, _pClassLinkage, _ppVertexShader);
}

HRESULT Device::CopyCreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, UINT _NumElements, const void* _pShaderBytecodeWithInputSignature, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout)
{
    return g_pd3dDevice->CreateInputLayout(_pInputElementDescs, _NumElements, _pShaderBytecodeWithInputSignature, _BytecodeLength, _ppInputLayout);
}

HRESULT Device::CopyCreatePixelShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader)
{
    return g_pd3dDevice->CreatePixelShader(_pShaderBytecode, _BytecodeLength, _pClassLinkage, _ppPixelShader);
}

HRESULT Device::CopyCreateBuffer(const D3D11_BUFFER_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Buffer** _ppBuffer)
{
    return g_pd3dDevice->CreateBuffer(_pDesc, _pInitialData, _ppBuffer);
}

/*HRESULT Device::CopyD3DX11CreateShaderResourceViewFromFile(ID3D11Device* _pDevice, LPCTSTR _pSrcFile, D3DX11_IMAGE_LOAD_INFO* _pLoadInfo, ID3DX11ThreadPump* _pPump, ID3D11ShaderResourceView** _ppShaderResourceView, HRESULT* _pHResult)
{
    return E_NOTIMPL;
}*/

HRESULT Device::CopyCreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState)
{
    return g_pd3dDevice->CreateSamplerState(_pSamplerDesc, _ppSamplerState);
}
