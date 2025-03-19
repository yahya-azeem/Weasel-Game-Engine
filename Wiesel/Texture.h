#pragma once
#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(WeaselGraphics::GraphicsDevice & gfx, const class Surface& s);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};