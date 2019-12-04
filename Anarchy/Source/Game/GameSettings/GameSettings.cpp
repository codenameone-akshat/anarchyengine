#include <iterator>

#include "GameSettings.h"

namespace anarchy::game::settings
{
	void GameSettings::AddShaderFilesToList(std::vector<framework::AC_String>& shaderFilePathList)
	{
		m_shaderFilePaths.reserve(m_shaderFilePaths.size() + shaderFilePathList.size());
		std::move(shaderFilePathList.begin(), shaderFilePathList.end(), std::back_inserter(m_shaderFilePaths));
	}
}
