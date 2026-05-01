#pragma once
#include"SwapChain.h"
#include<vector>

using Microsoft::WRL::ComPtr;

class RenderTarget final
{
	std::vector<ComPtr<ID3D12Resource>> render_targets_;
	D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle_{};
	UINT rtv_descriptor_size_ = 0;
public:
	RenderTarget() = default;
	~RenderTarget() = default;
	
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	RenderTarget(const RenderTarget&&) = delete;
	RenderTarget&& operator=(const RenderTarget&&) = delete;

	[[nodiscard]] bool create_render_target(ID3D12Device* device, IDXGISwapChain4* swapchain,
		ID3D12DescriptorHeap* rtv_heap, const UINT& buffer_size);

	[[nodiscard]] ID3D12Resource* get_render_target(const size_t& index) const noexcept;

	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_rtv_handle(const size_t& index) const noexcept;
};