#pragma once
#include<memory>
#include<cstdint>
#include<vector>

class RendererCore;
class CommandAllocator;
class CommandList;
class SwapChain;
class DescriptorHeap;
class RenderTarget;

class windowBase;

struct HWND__;
using HWND = HWND__*;

class RendererPeripheral final
{
	RendererCore* renderer_core{};

	std::unique_ptr<CommandAllocator>	allocator_{};
	std::unique_ptr<CommandList>		list_{};
	std::unique_ptr<SwapChain>			swapchain_{};
	std::unique_ptr<DescriptorHeap>		rtv_heap_{};
	std::unique_ptr<RenderTarget>		render_target_{};

	std::vector<uint64_t> frameFenceValue_;
public:
	RendererPeripheral();
	~RendererPeripheral();

	RendererPeripheral(const RendererPeripheral&) = delete;
	RendererPeripheral& operator=(const RendererPeripheral&) = delete;
	RendererPeripheral(const RendererPeripheral&&) = delete;
	RendererPeripheral& operator=(const RendererPeripheral&&) = delete;

	[[nodiscard]] bool initalize(RendererCore* core, windowBase* window,const int& buffercount);
	
	void update();

	void end();
};