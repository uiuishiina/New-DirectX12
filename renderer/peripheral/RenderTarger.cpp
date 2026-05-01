#include"RenderTarget.h"
#include"../../Debug/Debug.h"


[[nodiscard]] bool RenderTarget::create_render_target(ID3D12Device* device, IDXGISwapChain4* swapchain,
	ID3D12DescriptorHeap* rtv_heap, const UINT& buffer_size)	{

	render_targets_.resize(static_cast<size_t>(buffer_size));

	rtv_descriptor_size_ = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	rtv_descriptor_size_ = rtv_descriptor_size_;

	rtv_handle_ = rtv_heap->GetCPUDescriptorHandleForHeapStart();
	auto handle = rtv_handle_;
	
	for (UINT i = 0; i < buffer_size; ++i) {
		const auto hr = swapchain->GetBuffer(i, IID_PPV_ARGS(&render_targets_[i]));
		if (FAILED(hr)) {
			LOG_ERROR(LOG_VALUE(hr));
			return false;
		}

		D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
		rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		device->CreateRenderTargetView(render_targets_[i].Get(), &rtv_desc, handle);
		handle.ptr += rtv_descriptor_size_;
	}
	return true;
}

[[nodiscard]] ID3D12Resource* RenderTarget::get_render_target(const size_t& index) const noexcept {
	ASSERT(index < render_targets_.size());
	ASSERT(render_targets_[index]);
	return render_targets_[index].Get();
}

[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle(const size_t& index) const noexcept {
	ASSERT(index < render_targets_.size());
	auto handle = rtv_handle_;
	handle.ptr += index * rtv_descriptor_size_;
	return handle;
}