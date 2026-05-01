#include"CommandQueue.h"
#include"../../Debug/Debug.h"

[[nodiscard]] bool CommandQueue::create_queue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type) {

	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = type;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	const auto hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue_));
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
		return false;
	}
	return true;
}

[[nodiscard]] ID3D12CommandQueue* CommandQueue::get_queue()const noexcept {
	ASSERT(queue_);
	return queue_.Get();
}