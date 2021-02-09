#ifndef _GFX_MANAGER_H_
#define _GFX_MANAGER_H_

#include <Graphics/PlatformRenderer.h>

namespace anarchy
{
    class GfxManger
    {
        DECLARE_DEFAULT_CLASSMEMBERS(GfxManger);
    public:
        void Initialize();
        void Shutdown();

        void PreRender();
        void Render();
        void PostRender();

    private:
        void HandleEvents();

        std::unique_ptr<GfxRenderer> m_renderer = std::make_unique<RenderAPI>();
    };
}

#endif // !_GFX_MANAGER_H_

