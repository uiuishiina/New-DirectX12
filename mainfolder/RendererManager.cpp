#include"../renderer/core/RendererCore.h"

#include"RendererManager.h"
#include"../Debug/Debug.h"

RendererManager::RendererManager() = default;
RendererManager::~RendererManager() = default;

[[nodiscard]] bool RendererManager::initalize() {

	renderer_core = std::make_unique<RendererCore>();
	if (!renderer_core->initalize()) {
		return false;
	}
	return true;
}

[[nodiscard]] bool RendererManager::create_peripheral(windowContext& contest) {

	renderer_peripheral = std::make_unique<RendererPeripheral>();
	if (!renderer_peripheral->initalize(renderer_core.get(), contest, 3)) {
		return false;
	}

	return true;
}

void RendererManager::update() {
	renderer_peripheral->update();
}
void RendererManager::end() {
	
}