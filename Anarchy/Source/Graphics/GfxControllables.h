#ifndef _GFX_CONTROLLABLES_
#define _GFX_CONTROLLABLES_

namespace anarchy
{
    class GfxControllables
    {
        DECLARE_DEFAULT_CLASSMEMBERS_DELETED_CTOR(GfxControllables);
    
        DECLARE_DEFAULT_PROPERTY_STATIC(Vector4f, clearColor, ClearColor);
        DECLARE_DEFAULT_PROPERTY_STATIC(Vector4f, primitiveColor, PrimitiveColor);
        DECLARE_DEFAULT_PROPERTY_STATIC(PipelineState, pipelineState, PipelineState);

        DECLARE_PROPERTY_STATIC(float32, FOV, FOV, 60.0f);
        DECLARE_PROPERTY_STATIC(float32, camTranslationSpeedMult, CamTranslationSpeedMult, 0.07f);
        DECLARE_PROPERTY_STATIC(float32, camRotationSpeedMult, CamRotationSpeedMult, 0.12f);
    };
}

#endif // !_GFX_CONTROLLABLES_
