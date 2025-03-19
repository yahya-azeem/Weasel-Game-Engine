#include "Bindable.h"
#include <stdexcept>

ID3D11DeviceContext* Bindable::GetContext(WeaselGraphics::GraphicsDevice& gfx) noexcept
{
	return gfx.GetpContext();
}

ID3D11Device* Bindable::GetDevice(WeaselGraphics::GraphicsDevice& gfx) noexcept
{
	return gfx.GetpDevice();
}

DxgiInfoManager& Bindable::GetInfoManager(WeaselGraphics::GraphicsDevice& gfx) noexcept(!IS_DEBUG)
{
#ifndef NDEBUG
	return gfx.GetinfoManager();
#else
	throw std::logic_error("You Fucked Up! (tried to access gfx.infoManager in Release config)");
#endif
}