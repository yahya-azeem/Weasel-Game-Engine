#pragma once
#include <vector>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "..//Win.h"
#include "../Exception.h"
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../Helpers.h"
#include <vector>	
#include "../DxgiInfoManager.h"
#include <wrl.h>
#include <chrono>





class DirectX12Core 
{
public:
	class GraphicsException : public Exception
	{
		using Exception::Exception;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
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
	DirectX12Core(HWND hWnd);
	DirectX12Core(const DirectX12Core&) = delete;
	DirectX12Core& operator=(const DirectX12Core&) = delete;
	~DirectX12Core() = default;
	void EndFrame();
	void Render();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void UpdateRenderTargetViews(Microsoft::WRL::ComPtr<ID3D12Device2> device,Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap);
	uint64_t Signal(Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, Microsoft::WRL::ComPtr<ID3D12Fence> fence,uint64_t& fenceValue);
	void Flush(Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, Microsoft::WRL::ComPtr<ID3D12Fence> fence,uint64_t& fenceValue, HANDLE fenceEvent);
	void WaitForFenceValue(Microsoft::WRL::ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent);
	bool CheckTearingSupport();
	HANDLE CreateEventHandle();
	static const uint8_t pNumFrames = 3;

	//DirectX12 Public Functions
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);
	Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);
	Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateCommandList(Microsoft::WRL::ComPtr<ID3D12Device2> device, Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);
	Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence(Microsoft::WRL::ComPtr<ID3D12Device2> device);
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter);

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
	};

private:
	void EnableDebugLayer()
	{
	#ifndef NDEBUG
			ComPtr<ID3D12Debug> debugInterface;
			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
			debugInterface->EnableDebugLayer();
	#endif
	}
	bool pVSync = true;
	bool pTearingSupported = false;
	bool GfxInitialized = false;
	unsigned int pBufferIndex;
	char pVideoCardDescription[128];
	//BUNCH OF BULLSHIT
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT result;
	unsigned int numModes, i, numerator, denominator, renderTargetViewDescriptorSize;
	unsigned long long stringLength;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	bool pUseWarp = false;
	// DirectX12 Objects
	Microsoft::WRL::ComPtr<ID3D12Device2> pDevice;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> pCommandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> pSwap;
	Microsoft::WRL::ComPtr<ID3D12Resource> pBackBuffers[pNumFrames]; // TODO make this have a variable instead of two
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> pCommandList;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pCommandAllocator[pNumFrames]; //TODO same to this one
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pRTVDescriptorHeap;
	
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineStateObject; // pso containing a pipeline state
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature; //root signature defines data shaders will access
	D3D12_VIEWPORT Viewport; // area that output from rasterizer will be stretched to
	D3D12_RECT ScissorRect; // the area to draw in. pixels outside that area will not be drawn into
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer; // a default buffer in GPU memory that we will load vertex data for our triangle into
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView; // a structure containing a pointer to othe vertex data in gpu memory
												// the total size of the buffer, and the size of each element(vertex)

	


	UINT pRTVDescriptorSize;
	UINT pCurrentBackBufferIndex;
	Microsoft::WRL::ComPtr<ID3D12Fence> pFence;
	uint64_t pFenceValue = 0; 
	uint64_t pFrameFenceValues[pNumFrames] = {};
	HANDLE pFenceEvent;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	//TODO CHECK WTF DOES THIS DO
	D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc;
	D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle;
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
	Microsoft::WRL::ComPtr<IDXGIOutput> adapterOutput;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pPipelineState = nullptr;


	


	//8=================D
};

