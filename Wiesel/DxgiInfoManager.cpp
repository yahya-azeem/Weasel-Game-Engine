#include "DxgiInfoManager.h"
#include "Window.h"
#include "DirectX11/DirectX11Core.h"
#include <memory>
#include "WindowsThrowMacros.h"

#pragma comment(lib, "dxguid.lib")

#define GFX_THROW_NOINFO(hrcall) if(FAILED(hr = (hrcall))) throw DirectX11Core::HrException(__LINE__,__FILE__,hr)



DxgiInfoManager::DxgiInfoManager()
{
	//define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	//load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryExA("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
	{
		throw HWND_LAST_EXCEPT();
	}

	//Get address of DXGIGetDEbuginterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>
	(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
	);
	if (DxgiGetDebugInterface == nullptr)
	{
		throw HWND_LAST_EXCEPT();
	}

	HRESULT hr;
	GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));


}



void DxgiInfoManager::Set() noexcept
{
	//Set the index(next) so that the next all the GetMessages()
	// will only get errors generated after this call
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++)
	{
		HRESULT hr;
		SIZE_T messageLength;
		// get the size of message i in bytes
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

		//get the message and push its description into the vector
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
