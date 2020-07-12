#ifndef _GFX_RENDERER_H_
#define _GFX_RENDERER_H_

namespace anarchy
{
    class GfxRenderer
    {
    public:
        GfxRenderer() = default;
        ~GfxRenderer() = default;

        virtual void Initialize() {};
        virtual void PreRender() {};
        virtual void Render() {};
        virtual void PostRender() {};
        virtual void Destruct() {};
    };
}

#endif // !_GFX_RENDERER_H_

