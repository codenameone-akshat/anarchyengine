#ifndef _SANDBOX_INTERFACE_H_
#define _SANDBOX_INTERFACE_H_

#define ENABLE_SUPER_CALLS 1
#if ENABLE_SUPER_CALLS
#define SUPER_CALL(x) x
#else
#define SUPER_CALL(x) 
#endif

#include <Framework/GameSpecificInterface.h>

namespace anarchy
{
	GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_DECLARE;

	namespace sandbox
	{
		class DebugUI;
		class SandboxInterface : public GameSpecificInterface
		{
			DECLARE_SUPERCLASS(GameSpecificInterface);
			VIRTUAL_DTOR_GUARD(GameSpecificInterface);

		public:
			virtual void Initialize() override;

			virtual void Update() override;

			virtual void PreRender() override;

			virtual void Render() override;

			virtual void PostRender() override;

			virtual void Shutdown() override;

        private:
            std::unique_ptr<DebugUI> m_debugUI = std::make_unique<DebugUI>();
		};
	}
}

#endif // !_SANDBOX_INTERFACE_H_
