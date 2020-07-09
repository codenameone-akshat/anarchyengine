#ifndef _GAME_SETTINGS_H_ 
#define _GAME_SETTINGS_H_

#include <vector>

#include "../../Framework/Includes/FrameworkAliases.h"
#include "../../Engine/Graphics/HLSL/HLSLShader.h"

namespace anarchy::game
{
	// Transfer to .ini file later.
	class GameSettings
	{
	public:
		GameSettings() = default;
		~GameSettings() = default;
	
		inline std::vector<HLSLShader> GetAllShaders() const noexcept { return m_shaderList; }

		// TODO: Later maybe have AddVertexShader, AddPixelShader. Fill desc automatically. :)
		void AddShaderFileToList(AC_String fileName, HLSLShaderDesc shaderDesc, bool isInDeaultLocation = true);
	
	private:
		std::vector<HLSLShader> m_shaderList = {};
	};
}

#endif // _GAME_SETTINGS_H_