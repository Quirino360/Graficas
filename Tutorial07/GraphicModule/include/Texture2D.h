#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#endif

class Texture2D
{
public:
	Texture2D();
	~Texture2D();



private:
#if defined(DX11)
	ID3D11Texture2D* textureDX11;
#endif

public:
#if defined(DX11)
	ID3D11Texture2D*& getTextureDX11() { return textureDX11; };
	//void setBufferDX11(ID3D11Texture2D _newValue) { *textureDX11 = _newValue; };
	void ReleaseDX11();
#endif

private:

};

