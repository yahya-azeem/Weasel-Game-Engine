#pragma once
#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(WeaselGraphics::GraphicsDevice& gfx);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};