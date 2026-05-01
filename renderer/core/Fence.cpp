#include"Fence.h"
#include"../../Debug/Debug.h"

[[nodiscard]] bool Fence::create_fence(ID3D12Device* device) {

	const auto hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
		return false;
	}

	//	フェンスイベントの作成
	wait_frame_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (wait_frame_event_ == nullptr) {
		LOG_ERROR(LOG_HEADER(Message, "Failed to create fence event"));
		return false;
	}

	return true;
}

[[nodiscard]] ID3D12Fence* Fence::get_fence() const noexcept {
	ASSERT(fence_);
	return fence_.Get();
}

[[nodiscard]] UINT64 Fence::signal(ID3D12CommandQueue* command_queue) noexcept {
	ASSERT(fence_);
	next_frame_value_++;
	const auto hr = command_queue->Signal(fence_.Get(), next_frame_value_);
	if (FAILED(hr)) {
		LOG_ERROR(LOG_VALUE(hr));
	}
	return next_frame_value_;
}

[[nodiscard]] UINT64 Fence::get_completed_value() const noexcept {
	ASSERT(fence_);
	return fence_->GetCompletedValue();
}

void Fence::wait_event(UINT64& fence_value) const noexcept {
	ASSERT(fence_);
	if (fence_->GetCompletedValue() < fence_value) {
		fence_->SetEventOnCompletion(fence_value, wait_frame_event_);
		WaitForSingleObject(wait_frame_event_, INFINITE);
	}
}