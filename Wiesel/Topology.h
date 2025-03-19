#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(WeaselGraphics::GraphicsDevice& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};