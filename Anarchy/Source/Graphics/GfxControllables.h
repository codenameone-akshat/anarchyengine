#ifndef _GFX_CONTROLLABLES_
#define _GFX_CONTROLLABLES_

namespace anarchy
{
    class GfxControllables
    {
        DECLARE_DEFAULT_CLASSMEMBERS_DELETED_CTOR(GfxControllables);
    
    public:
        DECLARE_DEFAULT_PROPERTY_STATIC(Vector4f, clearColor, ClearColor);
        DECLARE_DEFAULT_PROPERTY_STATIC(Vector4f, primitiveColor, PrimitiveColor);
    };
}

#endif // !_GFX_CONTROLLABLES_
