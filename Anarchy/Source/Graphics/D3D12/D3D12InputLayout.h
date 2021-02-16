#ifndef _INPUT_LAYOUT_H_
#define _INPUT_LAYOUT_H_

namespace anarchy
{
	struct InputLayout
	{
		inline static const std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayoutList =
		{
			{
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT, // Vector3f
				0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				0
			},
            {
                "NORMAL",
                0,
                DXGI_FORMAT_R32G32B32_FLOAT, // Vector3f
                0,
                D3D12_APPEND_ALIGNED_ELEMENT,
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
                0
            }
		};
	};
}
#endif // !_INPUT_LAYOUT_H_
