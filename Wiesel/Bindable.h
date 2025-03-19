#pragma once 
#include "Window.h"
class Bindable
{
public:
	virtual void Bind(WeaselGraphics::GraphicsDevice& gfx) noexcept = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(WeaselGraphics::GraphicsDevice& gfx) noexcept;
	static ID3D11Device* GetDevice(WeaselGraphics::GraphicsDevice& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(WeaselGraphics::GraphicsDevice& gfx) noexcept(!IS_DEBUG);

};