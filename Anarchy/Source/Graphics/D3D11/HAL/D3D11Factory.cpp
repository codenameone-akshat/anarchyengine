#ifdef AC_D3D11

#include <d3d11.h>
#include <d3d11_1.h>

#include "D3D11Factory.h"
#include "Framework/Includes/FrameworkGlobals.h"

#pragma comment(lib,"d3d11.lib")

namespace anarchy
{
	AC_ComPtr<IDXGIAdapter> D3D11Factory::GetD3D11SupportedHardwareAdapter() const
	{
		AC_ComPtr<IDXGIAdapter> hardwareAdapter;

		auto enumAdapter = [&hardwareAdapter](uint32_t adapterIdx, AC_ComPtr<IDXGIFactory> factory)
		{
			return (factory->EnumAdapters(adapterIdx, &hardwareAdapter) != DXGI_ERROR_NOT_FOUND);
		};

		uint32_t adapterIdx = 0;
		while (enumAdapter(adapterIdx++, m_factory))
		{
			DXGI_ADAPTER_DESC adapterDesc;

			hardwareAdapter->GetDesc(&adapterDesc);

			std::array<D3D_FEATURE_LEVEL, 2> featureLevels{ D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
			uint32_t deviceFlags = NULL;

#ifdef AC_DEBUG
			deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // AC_DEBUG
			
			if (SUCCEEDED(D3D11CreateDevice(hardwareAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, deviceFlags, 
				featureLevels.data(), static_cast<uint32_t>(featureLevels.size()), D3D11_SDK_VERSION, nullptr, nullptr, nullptr)))
				break; // Exit on first hardware device that supports D3D11
		}

		return (hardwareAdapter);
	}
}

#endif // AC_D3D11