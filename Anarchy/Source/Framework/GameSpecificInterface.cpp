#include "acpch.h"
#include "GameSpecificInterface.h"

namespace anarchy
{
	// Extern Create Function
	GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_DECLARE;

	void GameSpecificInterface::Initialize()
	{

	}
	
	void GameSpecificInterface::Update()
	{

	}
	
	void GameSpecificInterface::PreRender()
	{
	
	}
	
	void GameSpecificInterface::Render()
	{
	
	}
	
	void GameSpecificInterface::PostRender()
	{
	
	}
	
	void GameSpecificInterface::Shutdown()
	{
	
	}
	void GameSpecificInterface::SetupGameSpecificInstance()
	{
		GAME_SPECIFIC_INTERFACE_CREATEINSTANCE;
	}
}
