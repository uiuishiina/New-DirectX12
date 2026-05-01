#pragma once
#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class Fence final
{
	ComPtr<ID3D12Fence> fence_{};
	HANDLE	wait_frame_event_{};
	UINT64	next_frame_value_{};
public:
	Fence() = default;
	~Fence() = default;

	Fence(const Fence&) = delete;
	Fence& operator=(const Fence&) = delete;
	Fence(const Fence&&) = delete;
	Fence&& operator=(const Fence&&) = delete;

	[[nodiscard]] bool create_fence(ID3D12Device* device);

	[[nodiscard]] ID3D12Fence* get_fence()const noexcept;

	[[nodiscard]] UINT64 signal(ID3D12CommandQueue* command_queue) noexcept;

	[[nodiscard]] UINT64 get_completed_value()const noexcept;

	void wait_event(UINT64& value)const noexcept;
};