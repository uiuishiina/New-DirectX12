#include"../window/window.h"
#include"../renderer/peripheral/RendererPeripheral.h"

#include"RenderUnit.h"
#include"../Debug/Debug.h"

[[nodiscard]] bool RenderUnit::initalize_unit(windowBase* window, RendererPeripheral* renderer) {

	window_ = window;
	renderer_ = renderer;

	ASSERT(window_);
	ASSERT(renderer_);

	return true;
}

[[nodiscard]] windowBase* RenderUnit::get_window()const noexcept {
	ASSERT(window_);
	return window_;
}

[[nodiscard]] RendererPeripheral* RenderUnit::get_renderer()const noexcept {
	ASSERT(renderer_);
	return renderer_;
}

void RenderUnit::update() {
	renderer_->update();
}