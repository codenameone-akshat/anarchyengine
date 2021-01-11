#ifndef _PLATFORM_RENDERER_
#define _PLATFORM_RENDERER_

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)
#include "Graphics/D3D12/D3D12Renderer.h"
using RenderAPI = anarchy::D3D12Renderer;
#elif AC_VULKAN
#include "Graphics/Vulkan/VulkanRenderer.h"
using RenderAPI = anarchy::VulkanRenderer;
#endif // AC_D3D12 | AC_D3D11 | AC_VULKAN


#endif // !_PLATFORM_RENDERER_
