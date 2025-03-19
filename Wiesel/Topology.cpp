#include "Topology.h"

Topology::Topology(WeaselGraphics::GraphicsDevice& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
	:
	type(type)
{}

void Topology::Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept
{
	GetContext(gfx)->IASetPrimitiveTopology(type);
}