#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

class CommandAllocator final
{
	std::vector<ComPtr<ID3D12CommandAllocator>> allocators_;
public:
	CommandAllocator() = default;
	~CommandAllocator() = default;

	CommandAllocator(const CommandAllocator&) = delete;
	CommandAllocator& operator=(const CommandAllocator&) = delete;
	CommandAllocator(const CommandAllocator&&) = delete;
	CommandAllocator&& operator=(const CommandAllocator&&) = delete;

	[[nodiscard]] bool create_command_allocator(ID3D12Device* device, const size_t& buffer_size, 
		D3D12_COMMAND_LIST_TYPE type);

	[[nodiscard]] ID3D12CommandAllocator* get_command_allocator(const size_t& index) const noexcept;

	void reset_command_allocator(const size_t& index);
};