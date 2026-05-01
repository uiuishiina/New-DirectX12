#pragma once
#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class CommandQueue final
{
	ComPtr<ID3D12CommandQueue> queue_{};
public:
	CommandQueue() = default;
	~CommandQueue() = default;

	CommandQueue(const CommandQueue&) = delete;
	CommandQueue& operator=(const CommandQueue&) = delete;
	CommandQueue(const CommandQueue&&) = delete;
	CommandQueue& operator=(const CommandQueue&&) = delete;

	[[nodiscard]] bool create_queue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type);

	[[nodiscard]] ID3D12CommandQueue* get_queue()const noexcept;
};