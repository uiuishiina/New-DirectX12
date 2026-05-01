#include"CommandAllocator.h"
#include"../../Debug/Debug.h"

	
[[nodiscard]] bool CommandAllocator::create_command_allocator(ID3D12Device* device, const size_t& buffer_size,
	D3D12_COMMAND_LIST_TYPE type) {

	allocators_.resize(buffer_size);

	for (size_t i = 0; i < allocators_.size(); i++) {
		const auto hr = device->CreateCommandAllocator(type, IID_PPV_ARGS(&allocators_[i]));
		if (FAILED(hr)) {
			LOG_ERROR(LOG_VALUE(hr));
			return false;
		}
	}
	return true;
}

[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator(const size_t& index) const noexcept {
	ASSERT(index < allocators_.size());
	ASSERT(allocators_[index]);
	return allocators_[index].Get();
}

void CommandAllocator::reset_command_allocator(const size_t& index) {
	ASSERT(index < allocators_.size());
	ASSERT(allocators_[index] != nullptr);
	const auto hr = allocators_[index]->Reset();
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
	}
}