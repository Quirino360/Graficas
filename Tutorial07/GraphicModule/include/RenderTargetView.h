#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif

class RenderTargetView
{
public:

    RenderTargetView();
    ~RenderTargetView();


private:

#if defined(DX11)
    ID3D11RenderTargetView* RTV;
#endif

public:
#if defined(DX11)
    ID3D11RenderTargetView*& getRenderTargetViewDX11() { return RTV; };
    //void setBufferDX11(ID3D11Buffer _newValue) { *bufferDX11 = _newValue; };

    void ReleaseDX11();
#endif

private:

};

