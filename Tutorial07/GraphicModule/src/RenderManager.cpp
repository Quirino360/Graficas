#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::ReleaseDX11()
{
}

HRESULT RenderManager::CreateDeviceAndSwapChainDX11(IDXGIAdapter* _pAdapter, D3D_DRIVER_TYPE _DriverType, HMODULE _Software, UINT _Flags, const D3D_FEATURE_LEVEL* _pFeatureLevels, UINT _FeatureLevels, UINT _SDKVersion, const DXGI_SWAP_CHAIN_DESC* _pSwapChainDesc, IDXGISwapChain** _ppSwapChain, ID3D11Device** _ppDevice, D3D_FEATURE_LEVEL* _pFeatureLevel, ID3D11DeviceContext** _ppImmediateContext)
{
	return  D3D11CreateDeviceAndSwapChain(_pAdapter, _DriverType, _Software, _Flags, _pFeatureLevels, _FeatureLevels, _SDKVersion, _pSwapChainDesc, _ppSwapChain, _ppDevice, _pFeatureLevel, _ppImmediateContext);
}

HRESULT RenderManager::CreateRenderTargetViewDX11(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView)
{
	return DeviceDX11->CreateRenderTargetView(_pResource, _pDesc, _ppRTView);
}

HRESULT RenderManager::CreateTexture2DDX11(const D3D11_TEXTURE2D_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Texture2D** _ppTexture2D)
{
	return DeviceDX11->CreateTexture2D(_pDesc, _pInitialData, _ppTexture2D);
}

HRESULT RenderManager::CreateDepthStencilViewDX11(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDepthStencilView)
{
	return DeviceDX11->CreateDepthStencilView(_pResource, _pDesc, _ppDepthStencilView);
}

HRESULT RenderManager::CreateShaderResourceViewDX11(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc, ID3D11ShaderResourceView** _ppSRView)
{
	return DeviceDX11->CreateShaderResourceView(_pResource, _pDesc, _ppSRView);
}

HRESULT RenderManager::CreateVertexShaderDX11(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11VertexShader** _ppVertexShader)
{
	return DeviceDX11->CreateVertexShader(_pShaderBytecode, _BytecodeLength, _pClassLinkage, _ppVertexShader);
}

HRESULT RenderManager::CreateInputLayoutDX11(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, UINT _NumElements, const void* _pShaderBytecodeWithInputSignature, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout)
{
	return DeviceDX11->CreateInputLayout(_pInputElementDescs, _NumElements, _pShaderBytecodeWithInputSignature, _BytecodeLength, _ppInputLayout);
}

HRESULT RenderManager::CreatePixelShaderDX11(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader)
{
	return DeviceDX11->CreatePixelShader(_pShaderBytecode, _BytecodeLength, _pClassLinkage, _ppPixelShader);
}

HRESULT RenderManager::CreateBufferDX11(const D3D11_BUFFER_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Buffer** _ppBuffer)
{
	return DeviceDX11->CreateBuffer(_pDesc, _pInitialData, _ppBuffer);
}

HRESULT RenderManager::CreateSamplerStateDX11(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState)
{
	return DeviceDX11->CreateSamplerState(_pSamplerDesc, _ppSamplerState);
}

HRESULT RenderManager::CreateRasterizerStateDX11(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState)
{
	return DeviceDX11->CreateRasterizerState(_pRasterizerDesc, _ppRasterizerState);
}
