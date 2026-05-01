#include"DescriptorHeap.h"
#include"../../Debug/Debug.h"

[[nodiscard]] bool DescriptorHeap::create_heap(ID3D12Device* device, const D3D12_DESCRIPTOR_HEAP_TYPE& type,
	const UINT& num_descriptors, const bool& shader_flag) {

	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = type;
	desc.NumDescriptors = num_descriptors;
	desc.Flags = shader_flag ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	const auto hr = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap_));
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
		return false;
	}

	return true;
}

[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap::get_heap()const noexcept {
	ASSERT(heap_);
	return heap_.Get();
}