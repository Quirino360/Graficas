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

#include "PassS.h"

#include <vector>

namespace GraphicsModule
{
	class TechniqueS
	{
	public:
		TechniqueS();
		~TechniqueS();

	private:
		int normalTechnique;
		int specularTechnique;
		int textureMap;

	public:

		void CreatePass(const char* _vertexShaderPath, const char* _pixelShaderPath); //compile depend of the flags
		void AddDefine(std::string _define) { defines.push_back(_define); };

		// ------------------------- Getters ------------------------- //
		int GetNormalTechnique() { return normalTechnique; };
		int GetSpecularTechnique() { return specularTechnique; };
		int GetTextureMap() { return textureMap; };

		Shader GetShader() { return passes[0].GetShader(); }
		// ------------------------- Setters ------------------------- //
		void SetNormalTechnique(int _normalTechnique) { normalTechnique = _normalTechnique; };
		void SetSpecularTechnique(int _specularTechnique) { specularTechnique = _specularTechnique; };
		void SetTextureMap(int _textureMap) { textureMap = _textureMap; };

	private:
		std::vector<PassS> passes;
		std::vector<std::string> defines;
	};

}