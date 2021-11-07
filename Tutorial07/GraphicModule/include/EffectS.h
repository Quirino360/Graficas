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

#include "TechniqueS.h"
#include "Shader.h"
#include <vector>

#define TEXTURE_MAP_NORMAL 1
#define TEXTURE_MAP_SPECULAR 2
#define ALL_TEXTURE_MAPS ( TEXTURE_MAP_NORMAL | TEXTURE_MAP_SPECULAR)


namespace GraphicsModule
{
	enum class NORMAL_TECHNIQUES
	{
		VERTEX_SHADER = 0,
		PIXEL_SHADER,
		COUNT
	};

	enum class SPECULAR_TECHNIQUES
	{
		PHONG = 0,
		BLINN_PHONG,
		COUNT
	};

	class EffectS
	{
	public:
		EffectS();
		~EffectS();

		std::vector<TechniqueS> vTechniques;
		unsigned int activeTechnique = 0;

	private:


	public:
		void CreatePassFromString(std::string _vetexShader, std::string );
		void CreatePassFromFile();
		void CreatePass();

		void CreateAllTechniques();

		// ----- Setters 
		void SetActiveTechnique(NORMAL_TECHNIQUES _normalTechnique, SPECULAR_TECHNIQUES _specularTecnique, int _textureMap);
		void SetActiveTechnique(int n) { activeTechnique = n; };
		

		// ----- Getters 
		TechniqueS GetActiveTechnique() { return vTechniques[activeTechnique]; };
		Shader GetShader() { return vTechniques[activeTechnique].GetShader(); }

	private:

	};
}