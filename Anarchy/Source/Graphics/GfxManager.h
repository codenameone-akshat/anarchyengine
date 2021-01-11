#ifndef _GRAPHIC_MANAGER_H_
#define _GRAPHIC_MANAGER_H_

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
        std::unique_ptr<GfxRenderer> m_renderer = std::make_unique<RenderAPI>();
    };
}

#endif // !_GRAPHIC_MANAGER_H_

