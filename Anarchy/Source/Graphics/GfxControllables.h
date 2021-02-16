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
        DECLARE_PROPERTY_STATIC(float32, camTranslationSpeedMult, CamTranslationSpeedMult, 5.0f);
        DECLARE_PROPERTY_STATIC(float32, camRotationSpeedMult, CamRotationSpeedMult, 0.12f);
        DECLARE_PROPERTY_STATIC(Vector3f, lightDirection, LightDirection, Vector3f(1.0f, 1.0f, 0.3f));
        DECLARE_PROPERTY_STATIC(Vector4f, ambientLight, AmbientLight, Vector4f(0.5f, 0.5f, 0.5f, 0.5f));
    };
}

#endif // !_GFX_CONTROLLABLES_
