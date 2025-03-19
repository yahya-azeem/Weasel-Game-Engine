#pragma once
#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(WeaselGraphics::GraphicsDevice& gfx,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		ID3DBlob* pVertexShaderBytecode);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};