#pragma once

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>


#elif defined(OGL)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

// -------------------- Buffers --------------------//
struct cbNeverChanges // b0
{
#if defined(DX11)
    XMMATRIX mView;
#endif
};

struct cbChangeOnResize // b1
{
#if defined(DX11)
    XMMATRIX mProjection;
#endif
};

struct CBChangesEveryFrame //b2
{
#if defined(DX11)
    XMMATRIX mWorld;
#endif
};

struct DirLight // b4
{
#if defined(DX11)
    XMFLOAT4 dir;
    XMFLOAT4 lightDirColor;
#endif
};

struct PointLight // b5
{
#if defined(DX11)
    XMFLOAT4 pointLightColor;
    XMFLOAT3 pointLightPos;
    FLOAT  pointLightAtt;
#endif
};

struct spotLight // b6
{
#if defined(DX11)
    XMFLOAT4 spotLightColor;
    XMFLOAT4 spotLightPos;
    XMFLOAT4 spotLightDir;
    FLOAT  SpotlightAtt;
    FLOAT  spotLightInner;
    FLOAT  spotLightOutner;
    FLOAT  n;
#endif
};

struct Ambient // b7
{
#if defined(DX11)
    XMFLOAT4 ambientColor;
    XMFLOAT3 n1;
    FLOAT kAmbient;
#endif
};

struct Specular // b8
{
#if defined(DX11)
    XMFLOAT3 n2;
    FLOAT kSpecular;
#endif
};

//#if defined(PHONG) || defined(BLINN_PHONG)
struct Shinies // b9
{
#if defined(DX11)
    XMFLOAT3 n3;
    FLOAT shininess;
#endif
};

struct Diffuse // b10
{
#if defined(DX11)
    XMFLOAT3 n4;
    FLOAT kDiffuse;
#endif
};

