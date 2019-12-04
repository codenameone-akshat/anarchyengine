#ifndef _GAME_SETTINGS_H_ 
#define _GAME_SETTINGS_H_

#include <vector>

#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::game::settings
{
	// Transfer to .ini file later.
	class GameSettings
	{
	public:
		GameSettings() = default;
		~GameSettings() = default;
	
		inline std::vector<framework::AC_String> GetAllShaderFiles() const noexcept { return m_shaderFilePaths; }
		inline void AddShaderFileToList(framework::AC_String shaderFilePath) { m_shaderFilePaths.emplace_back(shaderFilePath); }
		void AddShaderFilesToList(std::vector<framework::AC_String>& shaderFilePathList);
	
	private:
		std::vector<framework::AC_String> m_shaderFilePaths = {};
	};
}

#endif // _GAME_SETTINGS_H_