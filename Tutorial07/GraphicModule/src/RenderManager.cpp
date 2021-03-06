#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}
#if defined(DX11)

void RenderManager::ReleaseDX11()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------- Device ---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
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


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------ Device Context -----------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


void RenderManager::OMSetRenderTargetsDX11(UINT _NumViews, ID3D11RenderTargetView* const* _ppRenderTargetViews, ID3D11DepthStencilView* _pDepthStencilView)
{
	ImmediateContextDX11->OMSetRenderTargets(_NumViews, _ppRenderTargetViews, _pDepthStencilView);
}

void RenderManager::RSSetViewportsDX11(UINT _NumViewports, const D3D11_VIEWPORT* _pViewports)
{
	ImmediateContextDX11->RSSetViewports(_NumViewports, _pViewports);
}

void RenderManager::IASetPrimitiveTopologyDX11(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	ImmediateContextDX11->IASetPrimitiveTopology(_Topology);
}

void RenderManager::UpdateSubresourceDX11(ID3D11Resource* _pDstResource, UINT _DstSubresource, const D3D11_BOX* _pDstBox, const void* _pSrcData, UINT _SrcRowPitch, UINT _SrcDepthPitch)
{
	ImmediateContextDX11->UpdateSubresource(_pDstResource, _DstSubresource, _pDstBox, _pSrcData, _SrcRowPitch, _SrcDepthPitch);
}

void RenderManager::ClearRenderTargetViewDX11(ID3D11RenderTargetView* _pRenderTargetView, const FLOAT* _ColorRGBA)
{
	ImmediateContextDX11->ClearRenderTargetView(_pRenderTargetView, _ColorRGBA);
}

void RenderManager::ClearDepthStencilViewDX11(ID3D11DepthStencilView* _pDepthStencilView, UINT _ClearFlags, FLOAT _Depth, UINT8 _Stencil)
{
	ImmediateContextDX11->ClearDepthStencilView(_pDepthStencilView, _ClearFlags, _Depth, _Stencil);
}

void RenderManager::IASetInputLayoutDX11(ID3D11InputLayout* _pInputLayout)
{
	ImmediateContextDX11->IASetInputLayout(_pInputLayout);
}

void RenderManager::RSSetStateDX11(ID3D11RasterizerState* _pRasterizerState)
{
	ImmediateContextDX11->RSSetState(_pRasterizerState);
}

void RenderManager::IASetVertexBuffersDX11(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets)
{
	ImmediateContextDX11->IASetVertexBuffers(_StartSlot, _NumBuffers, _ppVertexBuffers, _pStrides, _pOffsets);
}

void RenderManager::IASetIndexBufferDX11(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _Format, UINT _Offset)
{
	ImmediateContextDX11->IASetIndexBuffer(_pIndexBuffer, _Format, _Offset);
}

void RenderManager::VSSetShaderDX11(ID3D11VertexShader* _pVertexShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _NumClassInstances)
{
	ImmediateContextDX11->VSSetShader(_pVertexShader, _ppClassInstances, _NumClassInstances);
}

void RenderManager::VSSetConstantBuffersDX11(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* const* _ppConstantBuffers)
{
	ImmediateContextDX11->VSSetConstantBuffers(_StartSlot, _NumBuffers, _ppConstantBuffers);
}

void RenderManager::PSSetShaderDX11(ID3D11PixelShader* _pPixelShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _NumClassInstances)
{
	ImmediateContextDX11->PSSetShader(_pPixelShader, _ppClassInstances, _NumClassInstances);
}

void RenderManager::PSSetConstantBuffersDX11(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* const* _ppConstantBuffers)
{
	ImmediateContextDX11->PSSetConstantBuffers(_StartSlot, _NumBuffers, _ppConstantBuffers);
}

void RenderManager::PSSetShaderResourcesDX11(UINT _StartSlot, UINT _NumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	ImmediateContextDX11->PSSetShaderResources(_StartSlot, _NumViews, _ppShaderResourceViews);
}

void RenderManager::PSSetSamplersDX11(UINT _StartSlot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplers)
{
	ImmediateContextDX11->PSGetSamplers(_StartSlot, _NumSamplers, _ppSamplers);
}

void RenderManager::DrawIndexedDX11(UINT _IndexCount, UINT _StartIndexLocation, INT _BaseVertexLocation)
{
	ImmediateContextDX11->DrawIndexed(_IndexCount, _StartIndexLocation, _BaseVertexLocation);
}






//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------- Eswap Chain -----------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

HRESULT RenderManager::GetBufferDX11(UINT _Buffer, REFIID _riid, void** _ppSurface)
{
	return SwapChainDX11->GetBuffer(_Buffer, _riid, _ppSurface);
}

HRESULT RenderManager::PresentDX11(UINT SyncInterval, UINT Flags)
{
	return SwapChainDX11->Present(SyncInterval, Flags);
}
#endif