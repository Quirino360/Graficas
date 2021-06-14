#include "TechniqueS.h"
#include <sstream>
#include <fstream>

namespace GraphicsModule
{
	TechniqueS::TechniqueS()
	{
		normalTechnique = 0;
		specularTechnique = 0;
		textureMap = 0;
	}

	TechniqueS::~TechniqueS()
	{
	}

	void TechniqueS::CreatePass(const char* _vertexShaderPath, const char* _pixelShaderPath)
	{

		std::ifstream vertexFile(_vertexShaderPath);
		std::stringstream vertexString;

		std::ifstream pixelFile(_pixelShaderPath);
		std::stringstream pixelString;

		//insert the defines to the string
		for (std::string& s : defines)
		{
			vertexString << "#define " << s << "\n";
		}

		//insert the file to the string
		while (!vertexFile.eof())
		{
			std::string s;
			std::getline(vertexFile, s);
			vertexString << s << "\n";
		}

		//insert the defines to the string
		for (std::string& s : defines)
		{
			pixelString << "#define " << s << "\n";
		}

		//insert the file to the string
		while (!pixelFile.eof())
		{
			std::string s;
			std::getline(pixelFile, s);
			pixelString << s << "\n";
		}

		//compile the shader with the pass(es)
		passes.push_back(PassS());
		passes[passes.size() - 1].CompileShader(vertexString.str().c_str(), pixelString.str().c_str());
	}
}