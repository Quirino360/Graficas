#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#elif defined(OGL)
#endif

struct Texture
{

};


class Material
{
public:
	Material();
	~Material();

private:
	int ID;
	Texture texture;


public:
	void SetMaterial();
	void Render();
};