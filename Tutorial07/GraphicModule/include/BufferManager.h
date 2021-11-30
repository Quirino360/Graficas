#pragma once
#include <windows.h>
#include <vector>

#include "Structs.h"

#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#endif

using namespace GraphicsModule;

class BufferManager
{
public:

    void Update();
    void Render();

    BufferManager();
    ~BufferManager();

    std::vector<bMatrix> m_matrix;

    std::vector<bFloat4> m_floats4;
    std::vector<bFloat3> m_floats3;
    std::vector<bFloat2> m_floats2;
    std::vector<bFloat> m_floats;

    std::vector<bInt4> m_ints4;
    std::vector<bInt3> m_ints3;
    std::vector<bInt2> m_ints2;
    std::vector<bInt> m_ints;

    std::vector<bBool> m_bools;

    std::vector<bResourceView> m_resourceViews; // Textures (ej. t0) // Estos son buffers
    std::vector<bSampler> m_Samplers; // Samplers (ej. s0) // Estos son buffers
    std::vector<bRenderTarget> m_renderTargetsView;

private:
public:
    bool CreateMatrix4x4(std::string _bufferName);

    bool CreateFloat4(std::string _bufferName);
    bool CreateFloat3(std::string _bufferName);
    bool CreateFloat2(std::string _bufferName);
    bool CreateFloat(std::string _bufferName);

    bool CreateInt4(std::string _bufferName);
    bool CreateInt3(std::string _bufferName);
    bool CreateInt(std::string _bufferName);
    bool CreateInt1(std::string _bufferName);

    bool CreateBool(std::string _bufferName);

    bool CreateResourceView(std::string _bufferName);
    bool CreateSampler(std::string _bufferName);
    bool CreateRenderTargetView(std::string _bufferName);

private:

};
