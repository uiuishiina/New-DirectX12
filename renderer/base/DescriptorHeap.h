#pragma once
#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class DescriptorHeap final
{
	ComPtr<ID3D12DescriptorHeap> heap_;
public:
	DescriptorHeap() = default;
	~DescriptorHeap() = default;

	DescriptorHeap(const DescriptorHeap&) = delete;
	DescriptorHeap& operator=(const DescriptorHeap&) = delete;
	DescriptorHeap(const DescriptorHeap&&) = delete;
	DescriptorHeap& operator=(const DescriptorHeap&&) = delete;

	[[nodiscard]] bool create_heap(ID3D12Device* device, const D3D12_DESCRIPTOR_HEAP_TYPE& type, 
		const UINT& num_descriptors, const bool& shader_flag);

	[[nodiscard]] ID3D12DescriptorHeap* get_heap()const noexcept;
};