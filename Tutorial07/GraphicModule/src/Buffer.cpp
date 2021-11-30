#include "Buffer.h"


Buffer::Buffer()
{
#if defined(DX11)
    bufferDX11 = nullptr;
#endif
}

Buffer::~Buffer()
{
#if defined(DX11)
    if (nullptr != bufferDX11)
    {
            //delete bufferDX11;
            //bufferDX11 = NULL;
    }

#endif
}

#if defined(DX11)
void Buffer::ReleaseDX11()
{
    bufferDX11->Release();
}
#endif