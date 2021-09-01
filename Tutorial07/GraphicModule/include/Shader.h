#pragma once
#include <windows.h>


#if defined(DX11)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>


#elif defined(OGL)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GraphicsModule
{
    class Shader
    {
    public:
        Shader() = default;
        Shader(const char* vertexPath, const char* fragmentPath);

        HWND g_hwnd; 
        unsigned int ID;

#if defined(DX11)
        ID3D11VertexShader* g_pVertexShader = NULL;
        ID3D11PixelShader* g_pPixelShader = NULL;
        ID3D11InputLayout* g_pVertexLayout = NULL;

#elif defined (OGL)
#endif
    //-----------------------
    private:



    //-----------------------
    public:
        HRESULT CompileCreateShadersFromString(const char* _vertexString, const char* _pixelString);

#if defined (DX11)
        HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

#elif defined (OGL)
        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
#endif
    public:
        void CreateShader(const char* vertexPath, const char* fragmentPath);



#if defined (DX11)
#elif defined (OGL)
        void setVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
        void setVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
        // ------------------------------------------------------------------------
        void setVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
        void setVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
        // ------------------------------------------------------------------------
        void setVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
        void setVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
        // ------------------------------------------------------------------------
        void setMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
        // ------------------------------------------------------------------------
        void setMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
        // ------------------------------------------------------------------------
        void setMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
#endif
    };
}