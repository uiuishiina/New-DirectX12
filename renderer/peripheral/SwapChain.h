#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class SwapChain final
{
	ComPtr<IDXGISwapChain4> swapchain_;
public:
	SwapChain() = default;
	~SwapChain() = default;

	SwapChain(const SwapChain&) = delete;
	SwapChain& operator=(const SwapChain&) = delete;
	SwapChain(const SwapChain&&) = delete;
	SwapChain&& operator=(const SwapChain&&) = delete;

	[[nodiscard]] bool create_swapchain(IDXGIFactory6* factory, ID3D12CommandQueue* command_queue, HWND hwnd, 
		const UINT& width, const UINT& height, const UINT& buffer_size);

	[[nodiscard]] IDXGISwapChain4* get_swapchain() const noexcept;
};