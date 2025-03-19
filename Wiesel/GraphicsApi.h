#pragma once
#include "WeaselGraphics.h"
#include "Win.h"
#include <wrl.h>
#include <d3d11.h>
#include "DxgiInfoManager.h"
#include "WeaselEnginelibs/imgui/imgui_impl_dx11.h"
#include "WeaselEnginelibs/imgui/imgui_impl_win32.h"


namespace WeaselGraphics
{
	typedef uint8_t CommandList;
	static const CommandList COMMANDLIST_COUNT = 32;
	static const CommandList INVALID_COMMANDLIST = COMMANDLIST_COUNT;

	enum QUEUE_TYPE
	{
		QUEUE_GRAPHICS,
		QUEUE_COMPUTE,

		QUEUE_COUNT,
	};

	class GraphicsDevice
	{
	protected:
		static const uint32_t BUFFERCOUNT = 2;
		uint64_t FRAMECOUNT = 0;
		bool DEBUGDEVICE = false;
		uint32_t capabilities = 0;
		size_t SHADER_IDENTIFIER_SIZE = 0;
		size_t TOPLEVEL_ACCELERATION_STRUCTURE_INSTANCE_SIZE = 0;
		uint32_t VARIABLE_RATE_SHADING_TILE_SIZE = 0;
		uint64_t TIMESTAMP_FREQUENCY = 0;

	public:

		
		~GraphicsDevice() = default;
		uint32_t GetFormatStride(FORMAT value) const;

		bool IsFormatUnorm(FORMAT value) const;

		bool IsFormatBlockCompressed(FORMAT value) const;

		bool IsFormatStencilSupport(FORMAT value) const;
		virtual bool CreateDevice(HWND hWnd);
		virtual void EndFrame();
		virtual void DrawIndexed(UINT count);
		virtual void SetProjection(DirectX::FXMMATRIX proj);
		virtual DirectX::XMMATRIX GetProjection();
		virtual ID3D11DeviceContext* GetpContext()const = 0;
		virtual ID3D11Device* GetpDevice() const = 0;
		virtual void BeginFrame(float red, float green, float blue) const = 0;
		virtual void EnableImgui() ;
		virtual void DisableImgui() ;
		virtual bool IsImguiEnabled() const = 0;
		virtual void SetCamera(DirectX::FXMMATRIX cam) ;
		virtual DirectX::XMMATRIX GetCamera();


		//data
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX camera;
		

#ifndef NDEBUG

	virtual DxgiInfoManager& GetinfoManager() const = 0;

#endif

		


		

	};

}
