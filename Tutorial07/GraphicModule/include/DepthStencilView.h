#pragma once


#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif

class DepthStencilView
{
public:

    DepthStencilView();
    ~DepthStencilView();


private:

#if defined(DX11)
    ID3D11DepthStencilView* DSV;
#endif

public:
#if defined(DX11)
    ID3D11DepthStencilView*& getyDepthStencilViewDX11() { return DSV; };
    //void setBufferDX11(ID3D11Buffer _newValue) { *bufferDX11 = _newValue; };

    void ReleaseDX11();
#endif

private:

};

