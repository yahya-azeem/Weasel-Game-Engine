#pragma once
#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(WeaselGraphics::GraphicsDevice& gfx, const std::wstring& path);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};