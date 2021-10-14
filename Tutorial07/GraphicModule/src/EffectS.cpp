#include "EffectS.h"

namespace GraphicsModule
{
	EffectS::EffectS()
	{
	}

	EffectS::~EffectS()
	{
	}

	void EffectS::CreateAllTechniques()
	{
		for (int i = 0; i < static_cast<int>(NORMAL_TECHNIQUES::COUNT); i++)
		{
			for (int j = 0; j < static_cast<int>(SPECULAR_TECHNIQUES::COUNT); j++)
			{
				for (int k = 0; k <= ALL_TEXTURE_MAPS; k++)
				{
					TechniqueS techniqueAux;

					switch ((NORMAL_TECHNIQUES)i)
					{
					case NORMAL_TECHNIQUES::VERTEX_SHADER:
						techniqueAux.SetNormalTechnique(static_cast<int>(NORMAL_TECHNIQUES::VERTEX_SHADER));
						techniqueAux.AddDefine("VERTEX_LIGHT");
						break;
					case NORMAL_TECHNIQUES::PIXEL_SHADER:
						techniqueAux.SetNormalTechnique(static_cast<int>(NORMAL_TECHNIQUES::PIXEL_SHADER));
						techniqueAux.AddDefine("PIXEL_LIGHT");
						break;
					default:
						break;
					}

					switch ((SPECULAR_TECHNIQUES)j)
					{
					case SPECULAR_TECHNIQUES::PHONG:
						techniqueAux.SetSpecularTechnique(static_cast<int>(SPECULAR_TECHNIQUES::PHONG));
						techniqueAux.AddDefine("PHONG");
						break;
					case SPECULAR_TECHNIQUES::BLINN_PHONG:
						techniqueAux.SetSpecularTechnique(static_cast<int>(SPECULAR_TECHNIQUES::BLINN_PHONG));
						techniqueAux.AddDefine("BLINN_PHONG");
						break;
					}

					if (k & TEXTURE_MAP_NORMAL)
					{
						techniqueAux.SetTextureMap(TEXTURE_MAP_NORMAL);
						techniqueAux.AddDefine("NORMAL_MAP_PIXEL_LIGHT");
					}
					if (k & TEXTURE_MAP_SPECULAR)
					{
						techniqueAux.SetTextureMap(TEXTURE_MAP_SPECULAR);
						techniqueAux.AddDefine("SPECULAR_MAP_PIXEL_LIGHT");
					}

					vTechniques.push_back(techniqueAux);
					//make the push back of techinques vector
				}
			}

		}
	}

	void EffectS::CreatePass()
	{
		//first create all techniques posibles
		if (vTechniques.size() == 0)
		{
			CreateAllTechniques();
		}

		//then create the shader with the passes you want, with all the posible passes
		for (int i = 0; i < vTechniques.size(); i++)
		{
			vTechniques[i].CreatePass("DefaultVertexShader.fx", "DefaultPixelShader.fx");
			//vTechniques[i].CreatePass("DX11LightVertex.fx", "DX11LightPixel.fx");
		}
	}

	void EffectS::SetActiveTechnique(NORMAL_TECHNIQUES _normalTechnique, SPECULAR_TECHNIQUES _specularTecnique, int _textureMap)
	{
		for (int i = 0; i < vTechniques.size(); i++)
		{
			if (vTechniques[i].GetNormalTechnique() == static_cast<int>(_normalTechnique) && vTechniques[i].GetSpecularTechnique() == static_cast<int>(_specularTecnique) && vTechniques[i].GetTextureMap() == _textureMap)
			{
				activeTechnique = i;
			}
		}
	}
}