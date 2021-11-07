#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#endif


#if defined(DX11)
enum USAGE_DX11
{
    D3D11_USAGE_DEFAULT_DX11 = 0,
    D3D11_USAGE_IMMUTABLE_DX11,
    D3D11_USAGE_DYNAMIC_DX11,
    D3D11_USAGE_STAGING_DX11
};

struct BUFFER_DESC_DX11
{
    unsigned int ByteWidth;
    USAGE_DX11 Usage;
    unsigned BindFlags;
    unsigned CPUAccessFlags;
    unsigned MiscFlags;
    unsigned StructureByteStride;
};
#endif

class Buffer
{
public:

    Buffer();
    ~Buffer();


private:

#if defined(DX11)
    ID3D11Buffer* bufferDX11;
#endif

public:
#if defined(DX11)
    ID3D11Buffer*& getyBufferDX11() { return bufferDX11; };

    void ReleaseDX11();
#endif

private:

};

