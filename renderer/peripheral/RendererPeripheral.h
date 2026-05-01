#pragma once
#include<memory>

class RendererCore;
class CommandAllocator;
class CommandList;
class SwapChain;
class RenderTarget;

struct HWND__;
using HWND = HWND__*;

struct windowContext{
	HWND hwnd{};
	std::pair<uint16_t, uint16_t> size{};
};

class RendererPeripheral final
{
	RendererCore*	renderer_core{};

	std::unique_ptr<CommandAllocator>	allocator_{};
	std::unique_ptr<CommandList>		list_{};
	std::unique_ptr<SwapChain>			swapchain_{};
	std::unique_ptr<RenderTarget>		render_target_{};

	windowContext	window_context{};
public:
	RendererPeripheral();
	~RendererPeripheral();

	RendererPeripheral(const RendererPeripheral&) = delete;
	RendererPeripheral& operator=(const RendererPeripheral&) = delete;
	RendererPeripheral(const RendererPeripheral&&) = delete;
	RendererPeripheral& operator=(const RendererPeripheral&&) = delete;

	[[nodiscard]] bool initalize(RendererCore* core, const windowContext& context,const int& buffercount);
};