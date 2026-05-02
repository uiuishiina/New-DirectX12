#pragma once
#include<memory>

class DXGI;
class Device;
class CommandQueue;
class Fence;

class RendererCore final
{
	std::unique_ptr<DXGI>			dxgi_{};
	std::unique_ptr<Device>			device_{};
	std::unique_ptr<CommandQueue>	queue_{};
	std::unique_ptr<Fence>			fence_{};
public:
	RendererCore();
	~RendererCore();

	RendererCore(const RendererCore&) = delete;
	RendererCore& operator=(const RendererCore&) = delete;
	RendererCore(const RendererCore&&) = delete;
	RendererCore& operator=(const RendererCore&&) = delete;

	[[nodiscard]] bool initalize();

	[[nodiscard]] DXGI* get_DXGI()const noexcept;

	[[nodiscard]] Device* get_Device()const noexcept;

	[[nodiscard]] CommandQueue* get_CommandQueue()const noexcept;

	[[nodiscard]] Fence* get_fence()const noexcept;
};