#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;


class CommandList final
{
	ComPtr<ID3D12GraphicsCommandList> list_{};
public:
	CommandList() = default;
	~CommandList() = default;

	CommandList(const CommandList&) = delete;
	CommandList& operator=(const CommandList&) = delete;
	CommandList(const CommandList&&) = delete;
	CommandList&& operator=(const CommandList&&) = delete;

	[[nodiscard]] bool create_command_list(ID3D12Device* device, ID3D12CommandAllocator* allocator,
		D3D12_COMMAND_LIST_TYPE type);

	[[nodiscard]] ID3D12GraphicsCommandList* get_command_list() const noexcept;

	void reset_command_list(ID3D12CommandAllocator* allocator);
};