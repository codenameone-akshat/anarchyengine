#ifndef _GAME_SETTINGS_H_ 
#define _GAME_SETTINGS_H_

#include <vector>

#include "../../Framework/Includes/FrameworkAliases.h"
#include "../../Engine/Graphics/HLSL/HLSLShader.h"

namespace anarchy::game::settings
{
	// Transfer to .ini file later.
	class GameSettings
	{
	public:
		GameSettings() = default;
		~GameSettings() = default;
	
		inline std::vector<engine::graphics::HLSLShader> GetAllShaders() const noexcept { return m_shaderList; }

		// TODO: Later maybe have AddVertexShader, AddPixelShader. Fill desc automatically. :)
		void AddShaderFileToList(framework::AC_String fileName, engine::graphics::HLSLShaderDesc shaderDesc, bool isInDeaultLocation = true);
	
	private:
		std::vector<engine::graphics::HLSLShader> m_shaderList = {};
	};
}

#endif // _GAME_SETTINGS_H_