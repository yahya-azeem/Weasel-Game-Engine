#pragma once
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(WeaselGraphics::GraphicsDevice& gfx, const std::vector<unsigned short>& indices);
	void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept override;
	UINT GetCount() const noexcept;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};