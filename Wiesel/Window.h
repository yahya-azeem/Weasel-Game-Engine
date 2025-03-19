#pragma once
#include "Win.h"
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Xinput.h"
#include "GraphicsApi.h"
#include <optional>
#include "DirectX12/DirectX12Core.h"
#include "DirectX11/DirectX11Core.h"


class Window
{
public:
	class WindowException : public Exception
	{
		using Exception::Exception;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public WindowException
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;

		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public WindowException
	{
	public:
		using WindowException::WindowException;
		const char* GetType() const noexcept override;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const WCHAR* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const WCHAR* wndClassName = L"Weasel Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const WCHAR* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	void SetFullscreen(bool fullscreen);
	void CreateDefaultGraphicsApi();
	static std::optional<int> ProcessMessages();


	WeaselGraphics::GraphicsDevice& GraphicsDevice();
	//DirectX12Core& DirectX12Gfx();
	DirectX11Core& DirectX11Gfx();
	std::string OperatingSystem = "Win10";

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;

private:
	int width;
	int height;
	HWND hWnd;
	bool Fullscreen = false;
	RECT wr;

	//std::unique_ptr<DirectX12Core>  pDirectX12Gfx;
	DirectX11Core*  pDirectX11Gfx;
	WeaselGraphics::GraphicsDevice* pGfx;
	

};

