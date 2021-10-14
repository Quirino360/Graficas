#include "PassS.h"
#include "test.h"

namespace GraphicsModule
{
	PassS::PassS()
	{
	}

	PassS::~PassS()
	{
	}

	void PassS::CompileShader(const char* _vertexShader, const char* _pixelShader)
	{
        shaders.push_back(Shader());
        unsigned int count = shaders.size() - 1;
		shaders[count].CompileCreateShadersFromString(_vertexShader, _pixelShader);
	}
}