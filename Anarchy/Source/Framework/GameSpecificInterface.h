#ifndef _GAME_SPECIFIC_INTERFACE_
#define _GAME_SPECIFIC_INTERFACE_

// Helpers
#define GAME_SPECIFIC_INTERFACE_CREATEINSTANCE				CreateGameSpecificInstance()
#define GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_DECLARE		extern void CreateGameSpecificInstance()
#define GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_DECLARE void CreateGameSpecificInstance()
#define GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_BEGIN	void CreateGameSpecificInstance() {
#define GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_END		}

namespace anarchy
{
    class GameSpecificInterface
	{
	public:
		DECLARE_DEFAULT_CLASSMEMBERS_INTERFACE(GameSpecificInterface);

		virtual void Initialize();
		
		virtual void Update();
		
		virtual void PreRender();
		
		virtual void Render();
		
		virtual void PostRender();
		
		virtual void Shutdown();

		static void SetupGameSpecificInstance();

		static std::shared_ptr<GameSpecificInterface> GetInstance() { return ms_gameSpecificInstance; }
		static void SetInstance(std::shared_ptr<GameSpecificInterface> instance) { ms_gameSpecificInstance = instance; }

	protected:
		inline static std::shared_ptr<GameSpecificInterface> ms_gameSpecificInstance = nullptr;
	};

#define acGameSpecificInterface GameSpecificInterface::GetInstance()

}

#endif // !_GAME_SPECIFIC_INTERFACE_
