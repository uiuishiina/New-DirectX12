#include"CommandList.h"
#include"../../Debug/Debug.h"


[[nodiscard]] bool CommandList::create_command_list(ID3D12Device* device, ID3D12CommandAllocator* allocator,
	D3D12_COMMAND_LIST_TYPE type) {

	const auto hr = device->CreateCommandList(
		0,type,allocator,nullptr,IID_PPV_ARGS(&list_));
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
		return false;
	}

	list_->Close(); // コマンドリストは作成後にクローズする必要がある
	return true;
}

[[nodiscard]] ID3D12GraphicsCommandList* CommandList::get_command_list() const noexcept {
	ASSERT(list_);
	return list_.Get();
}

void CommandList::reset_command_list(ID3D12CommandAllocator* allocator) {
	ASSERT(list_);
	const auto hr = list_->Reset(allocator, nullptr);
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
	}
}