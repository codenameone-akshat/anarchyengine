#include <iterator>

#include "GameSettings.h"

namespace anarchy::game::settings
{
	void GameSettings::AddShaderFileToList(framework::AC_String fileName, engine::graphics::HLSLShaderDesc shaderDesc, bool isInDeaultLocation)
	{
		engine::graphics::HLSLShader shader(fileName, shaderDesc, isInDeaultLocation);
		
		// TODO: shader.Validate() before adding to vector.
		m_shaderList.emplace_back(shader);
	}
}
