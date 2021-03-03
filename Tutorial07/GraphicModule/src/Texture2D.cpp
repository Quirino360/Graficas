#include "Texture2D.h"

Texture2D::Texture2D()
{
#if defined(DX11)
	textureDX11 = NULL;
#endif
}

Texture2D::~Texture2D()
{
#if defined(DX11)
	if (nullptr != textureDX11)
	{
		delete textureDX11;
		textureDX11 = nullptr;
	}
	delete this;
#endif
}

#if defined(DX11)
void Texture2D::ReleaseDX11()
{
	textureDX11->Release();
}
#endif