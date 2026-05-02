#pragma once
#include<memory>

class windowBase;
class RendererPeripheral;

class RenderUnit final
{
	windowBase* window_{};
	RendererPeripheral* renderer_{};
public:
	[[nodiscard]] bool initalize_unit(windowBase* window, RendererPeripheral* renderer);

	[[nodiscard]] windowBase* get_window()const noexcept;

	[[nodiscard]] RendererPeripheral* get_renderer()const noexcept;

	void update();

	void end();
};