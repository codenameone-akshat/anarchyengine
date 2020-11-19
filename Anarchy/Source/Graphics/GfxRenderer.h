#ifndef _GFX_RENDERER_H_
#define _GFX_RENDERER_H_

namespace anarchy
{
    class GfxRenderer
    {
    public:
        GfxRenderer() = default;
        virtual ~GfxRenderer() = default;

        virtual void Initialize() {};
        virtual void PreRender() {};
        virtual void Render() {};
        virtual void PostRender() {};
        virtual void Shutdown() {};
    };
}

#endif // !_GFX_RENDERER_H_

