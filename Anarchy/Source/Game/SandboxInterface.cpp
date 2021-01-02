#include "acpch.h"
#include "SandboxInterface.h"

namespace anarchy
{
	// Instance Creation
	GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_BEGIN
		GameSpecificInterface::SetInstance(std::make_shared<SandboxInterface>());
	GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_END

	void SandboxInterface::Initialize()
	{
		SUPER_CALL(super::Initialize();)
	}
	
	void SandboxInterface::Update()
	{
		SUPER_CALL(super::Update();)
	}
	
	void SandboxInterface::PreRender()
	{
		SUPER_CALL(super::PreRender();)
	}
	
	void SandboxInterface::Render()
	{
		SUPER_CALL(super::Render();)
	}
	
	void SandboxInterface::PostRender()
	{
		SUPER_CALL(super::PostRender();)
	}
	
	void SandboxInterface::Shutdown()
	{
		SUPER_CALL(super::Shutdown();)
	}
}
