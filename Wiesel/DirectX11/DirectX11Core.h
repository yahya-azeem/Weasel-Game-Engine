#pragma once
//Linking
#pragma comment(lib, "d3d11.lib")

#include "../GraphicsApi.h"

#include "..//Win.h"
#include "..//Exception.h"
#include <d3d11.h>

#include <vector>	
#include "../DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

#include <wrl.h>



class DirectX11Core : public WeaselGraphics::GraphicsDevice
{
	friend class Bindable;
public:
	class GraphicsException : public Exception
	{
		using Exception::Exception;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) ;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept ;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};


public:
	DirectX11Core();
	DirectX11Core(const DirectX11Core&) = delete;
	DirectX11Core& operator=(const DirectX11Core&) = delete;
	~DirectX11Core() = default;
	bool CreateDevice(HWND hWnd)override;
	void EndFrame() override;
	
	void DrawIndexed(UINT count)  override;
	void SetProjection(DirectX::FXMMATRIX proj)  override;
	DirectX::XMMATRIX GetProjection()  override;
	DirectX::XMMATRIX projection;
	ID3D11DeviceContext* GetpContext() const override;
	ID3D11Device* GetpDevice() const override;
	void BeginFrame(float red, float green, float blue) const override;
	void EnableImgui()  override;
	void DisableImgui()  override;
	bool IsImguiEnabled() const override;
	 void SetCamera(DirectX::FXMMATRIX cam)  override;
	 DirectX::XMMATRIX GetCamera()  override;
public:
	bool imguiEnabled = true;

	

#ifndef NDEBUG
	DxgiInfoManager infoManager;
	DxgiInfoManager& GetinfoManager() const override
	{
		return infoManager;
	}
#endif // !NDEBUG

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
	




	//8=================D
};


