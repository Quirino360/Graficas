#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

private:
#if defined(DX11)
    ID3D11Device* DeviceDX11 = nullptr;
    ID3D11DeviceContext* ImmediateContextDX11 = nullptr;
    IDXGISwapChain* SwapChainDX11 = nullptr;

public:
#endif
    #if defined(DX11)
    // -------------------------- Device ------------------------ //
	HRESULT CreateDeviceAndSwapChainDX11(IDXGIAdapter* _pAdapter, D3D_DRIVER_TYPE _DriverType, HMODULE _Software, UINT _Flags, const D3D_FEATURE_LEVEL* _pFeatureLevels, UINT _FeatureLevels, UINT _SDKVersion, const DXGI_SWAP_CHAIN_DESC* _pSwapChainDesc, IDXGISwapChain** _ppSwapChain, ID3D11Device** _ppDevice, D3D_FEATURE_LEVEL* _pFeatureLevel, ID3D11DeviceContext** _ppImmediateContext);
	HRESULT CreateRenderTargetViewDX11(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView);
	HRESULT CreateTexture2DDX11(const D3D11_TEXTURE2D_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Texture2D** _ppTexture2D);
	HRESULT CreateDepthStencilViewDX11(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDepthStencilView);
    HRESULT CreateShaderResourceViewDX11(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc, ID3D11ShaderResourceView** _ppSRView);
	HRESULT CreateVertexShaderDX11(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11VertexShader** _ppVertexShader);
	HRESULT CreateInputLayoutDX11(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, UINT _NumElements, const void* _pShaderBytecodeWithInputSignature, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout);
	HRESULT CreatePixelShaderDX11(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader);
	HRESULT CreateBufferDX11(const D3D11_BUFFER_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Buffer** _ppBuffer);
	HRESULT CreateSamplerStateDX11(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState);
    HRESULT CreateRasterizerStateDX11(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState);

    // -------------------------- DeviceContext ------------------------ //
    void OMSetRenderTargetsDX11(UINT _NumViews, ID3D11RenderTargetView* const* _ppRenderTargetViews, ID3D11DepthStencilView* _pDepthStencilView);
    void RSSetViewportsDX11(UINT _NumViewports, const D3D11_VIEWPORT* _pViewports);
    void IASetPrimitiveTopologyDX11(D3D11_PRIMITIVE_TOPOLOGY _Topology);
    void UpdateSubresourceDX11(ID3D11Resource* _pDstResource,UINT _DstSubresource,const D3D11_BOX* _pDstBox, const void* _pSrcData,UINT _SrcRowPitch,UINT _SrcDepthPitch);
    void ClearRenderTargetViewDX11(ID3D11RenderTargetView* _pRenderTargetView, const FLOAT* _ColorRGBA);
    void ClearDepthStencilViewDX11(ID3D11DepthStencilView* _pDepthStencilView, UINT _ClearFlags, FLOAT _Depth, UINT8  _Stencil);
    void IASetInputLayoutDX11(ID3D11InputLayout* _pInputLayout);
    void RSSetStateDX11 (ID3D11RasterizerState* _pRasterizerState);
    void IASetVertexBuffersDX11(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);
    void IASetIndexBufferDX11(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT  _Format, UINT _Offset);

    void VSSetShaderDX11(ID3D11VertexShader* _pVertexShader, ID3D11ClassInstance* const* _ppClassInstances, UINT  _NumClassInstances);
    void VSSetConstantBuffersDX11(UINT _StartSlot,UINT _NumBuffers,ID3D11Buffer* const* _ppConstantBuffers);
    void PSSetShaderDX11(ID3D11PixelShader* _pPixelShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _NumClassInstances);
    void PSSetConstantBuffersDX11(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* const* _ppConstantBuffers);;
    void PSSetShaderResourcesDX11(UINT _StartSlot, UINT _NumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);
    void PSSetSamplersDX11(UINT _StartSlot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplers);
    void DrawIndexedDX11(UINT _IndexCount, UINT _StartIndexLocation, INT  _BaseVertexLocation);
    // -------------------------- EswapChain ------------------------ //


    // Relese
    void ReleaseDX11();
    // -------------------------- Getters ------------------------ //
    ID3D11Device*& getDeviceDX11() { return DeviceDX11; };
    ID3D11DeviceContext*& getDeviceContextDX11() { return ImmediateContextDX11; };
    IDXGISwapChain*& getSwapChainDX11() { return SwapChainDX11; };

#endif

private:
};

