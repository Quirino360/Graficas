#pragma once
#include <string>

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

#include "RenderTargetView.h"
#include "Buffer.h"

namespace GraphicsModule {
    struct float4 {
        float      x;
        float      y;
        float      z;
        float      w;

        float4() {};
        float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
        float4(const float* pArray)
        {
            x = pArray[0];
            y = pArray[1];
            z = pArray[2];
            w = pArray[3];
        }

        float4& operator= (const float4& Float4)
        {
            x = Float4.x;
            y = Float4.y;
            z = Float4.z;
            w = Float4.w;
            return *this;
        }
    };

    struct float3
    {
        float x;
        float y;
        float z;

        float3() {};
        float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
        float3(const float* pArray)
        {
            x = pArray[0];
            y = pArray[1];
            z = pArray[2];
        }

        float3& operator= (const float3& Float3)
        {
            x = Float3.x;
            y = Float3.y;
            z = Float3.z;
            return *this;
        }
    private:
        float NA = 0.0f;
    };

    struct float2
    {
        float x;
        float y;

        float2() {};
        float2(float _x, float _y) : x(_x), y(_y) {};
        float2(const float* pArray)
        {
            x = pArray[0];
            y = pArray[1];
        }

        float2& operator= (const float2& Float2)
        {
            x = Float2.x;
            y = Float2.y;
            return *this;
        }
        float NA = 0.0f;
        float NA2 = 0.0f;
    };

    struct int4 {
        int      x;
        int      y;
        int      z;
        int      w;

        int4() {};
        int4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {};
        int4(const int* pArray)
        {
            x = pArray[0];
            y = pArray[1];
            z = pArray[2];
            w = pArray[3];
        }

        int4& operator= (const int4& Float4)
        {
            x = Float4.x;
            y = Float4.y;
            z = Float4.z;
            w = Float4.w;
            return *this;
        }
    };

    struct int3 {
        int      x;
        int      y;
        int      z;

        int3() {};
        int3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {};
        int3(const int* pArray)
        {
            x = pArray[0];
            y = pArray[1];
            z = pArray[2];
        }

        int3& operator= (const int3& Float4)
        {
            x = Float4.x;
            y = Float4.y;
            z = Float4.z;
            return *this;
        }
    };

    struct int2 {
        int      x;
        int      y;

        int2() {};
        int2(int _x, int _y) : x(_x), y(_y) {};
        int2(const int* pArray)
        {
            x = pArray[0];
            y = pArray[1];
        }

        int2& operator= (const int2& Float4)
        {
            x = Float4.x;
            y = Float4.y;
            return *this;
        }
    };

    struct bFloat4
    {
        Buffer buffer;
        float4 values = { 0,0,0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bFloat3
    {
        Buffer buffer;
        float3 values = { 0,0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bFloat2
    {
        Buffer buffer;
        float2 values = { 0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bFloat
    {
        Buffer buffer;
        float values = { 0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bInt4
    {
        Buffer buffer;
        int4 values = { 0,0,0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bInt3
    {
        Buffer buffer;
        int3 values = { 0,0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bInt2
    {
        Buffer buffer;
        int2 values = { 0,0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };

    struct bInt
    {
        Buffer buffer;
        int values = { 0 };
        std::string name = "defaultName";
        bool clamp = false;
        float min = -1000;
        float max = 1000;
        unsigned int ID = 0;
    };


    struct bBool
    {
        Buffer buffer;
        bool values = false;
        std::string name = "defaultName";
        unsigned int ID = 0;
    };

    struct bMatrix
    {
        Buffer buffer;
        XMMATRIX values;
        std::string name = "defaultName";
        unsigned int ID = 0;
    };

    struct bResourceView
    {
        ID3D11ShaderResourceView* values;
        std::string name = "defaultName";
        unsigned int ID = 0;
    };

    struct bSampler
    {
        ID3D11SamplerState* values;
        std::string name = "defaultName";
        unsigned int ID = 0;
    };

    struct bRenderTarget
    {
        RenderTargetView values;
        std::string name = "defaultName";
        unsigned int ID = 0;
    };

    struct VIEWPORT
    {
#if defined(DX11)
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;
#endif
    };

    // ----- Buffers 
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

    struct CBChangesEveryFrame
    {
#if defined(DX11)
        XMMATRIX mWorld;
        XMFLOAT4 vMeshColor;
#endif
    };

    struct DirLight // b3
    {
#if defined(DX11)
        float4 dir;
        float4 lightDirColor;
#endif
    };

    struct PointLight // b4
    {
#if defined(DX11)
        float4 pointLightColor;
        float3 pointLightPos;
        float  pointLightAtt;
#endif
    };

    struct spotLight // b5
    {
#if defined(DX11)
        float4 spotLightColor;
        float4 spotLightPos;
        float4 spotLightDir;
        float  SpotlightAtt;
        float  spotLightInner;
        float  spotLightOutner;
        float  n;
#endif
    };

    struct Ambient // b6
    {
#if defined(DX11)
        float4 ambientColor;
        float3 n1;
        float kAmbient;
#endif
    };

    struct Specular // b7
    {
#if defined(DX11)
        float3 n2;
        float kSpecular;
#endif
    };

    //#if defined(PHONG) || defined(BLINN_PHONG)
    struct Shinies // b8
    {
#if defined(DX11)
        float3 n3;
        float shininess;
#endif
    };

    struct Diffuse // b9
    {
#if defined(DX11)
        float3 n4;
        float kDiffuse;
#endif
    };

}