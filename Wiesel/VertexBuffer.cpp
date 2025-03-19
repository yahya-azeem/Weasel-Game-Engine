#include "VertexBuffer.h"

void VertexBuffer::Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept
{
	const UINT offset = 0u;
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}