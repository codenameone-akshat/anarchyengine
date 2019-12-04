#ifndef _GFX_RENDERER_H_
#define _GFX_RENDERER_H_

namespace anarchy::engine::graphics
{
	class GfxRenderer
	{
	public:
		GfxRenderer() = default;
		~GfxRenderer() = default;

		virtual void Initialize() {};
		virtual void UpdateSingleThreaded() {};
		virtual void Destruct() {};
	};
}

#endif // !_GFX_RENDERER_H_

