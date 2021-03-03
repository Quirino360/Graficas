#pragma once
#include <d3d11.h>

class Device
{
public:
	Device();
	~Device();


private:
	ID3D11Device* g_pd3dDevice;

public:

	HRESULT CopyD3D11CreateDeviceAndSwapChain(IDXGIAdapter* _pAdapter, D3D_DRIVER_TYPE _DriverType, HMODULE _Software, UINT _Flags, const D3D_FEATURE_LEVEL* _pFeatureLevels, UINT _FeatureLevels, UINT _SDKVersion, const DXGI_SWAP_CHAIN_DESC* _pSwapChainDesc, IDXGISwapChain** _ppSwapChain, ID3D11Device** _ppDevice, D3D_FEATURE_LEVEL* _pFeatureLevel, ID3D11DeviceContext** _ppImmediateContext);
	/*long CreateDeviceAndSwapChain(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, 
								  IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext);*/


	HRESULT CopyCreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView);
	//to do// //long CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);

	HRESULT CopyCreateTexture2D(const D3D11_TEXTURE2D_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Texture2D** _ppTexture2D);
	//to do// //long CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D);

	HRESULT CopyCreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDepthStencilView);
	//to do// //long CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);

	HRESULT CopyCreateVertexShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11VertexShader** _ppVertexShader);
	//to do// //long CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader);

	HRESULT CopyCreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, UINT _NumElements, const void* _pShaderBytecodeWithInputSignature, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout);
	//to do// //long CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout);

	HRESULT CopyCreatePixelShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader);
	//to do// //long CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader);

	HRESULT CopyCreateBuffer(const D3D11_BUFFER_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, ID3D11Buffer** _ppBuffer);
	//to do// //long CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer);

	//HRESULT CopyD3DX11CreateShaderResourceViewFromFile(ID3D11Device* _pDevice, LPCTSTR _pSrcFile, D3DX11_IMAGE_LOAD_INFO* _pLoadInfo, ID3DX11ThreadPump* _pPump, ID3D11ShaderResourceView** _ppShaderResourceView, HRESULT* _pHResult);
	//to do// //long CreateShaderResourceViewFromFile(/*_In_*/  ID3D11Device* pDevice,/* _In_*/  LPCTSTR pSrcFile, /*_In_*/  D3DX11_IMAGE_LOAD_INFO* pLoadInfo, /*_In_*/  ID3DX11ThreadPump* pPump, /*_Out_*/ ID3D11ShaderResourceView** ppShaderResourceView, /*_Out_*/ HRESULT* pHResult); // i guess it is not necessary but I'll try
	
	HRESULT CopyCreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState);
	//to do// //long CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);

	//original// //unsigned long Release();

};

