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

#include "Shader.h"

#include <vector>

namespace GraphicsModule
{
	class PassS
	{
	public:
		PassS();
		~PassS();

	private:
		HRESULT hr = S_OK;
		std::vector<Shader> shaders;
		HWND g_hwnd;

	public:
		void CompileShader(const char* _vertexShader, const char* _pixelShader); //al the posible techniques
		Shader GetShader() { return shaders[0]; };

	private:
	};
}
