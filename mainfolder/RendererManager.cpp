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

[[nodiscard]] bool RendererManager::create_main_peripheral(windowBase* window) {

	main_peripheral = std::make_unique<RendererPeripheral>();
	if (!main_peripheral->initalize(renderer_core.get(), window, 3)) {
		return false;
	}

	return true;
}

[[nodiscard]] bool RendererManager::create_sub_peripheral(windowBase* window, windowID id) {

	auto sub = std::make_unique<RendererPeripheral>();
	if (!sub->initalize(renderer_core.get(), window, 3)) {
		return false;
	}
	sub_peripherals.emplace(id,std::move(sub));

	return true;
}

[[nodiscard]] RendererPeripheral* RendererManager::get_main_peripheral() {
	ASSERT(main_peripheral);
	return main_peripheral.get();
}

[[nodiscard]] RendererPeripheral* RendererManager::get_sub_peripheral(windowID id) {
	ASSERT(!sub_peripherals.empty());
	auto it = sub_peripherals.find(id);
	ASSERT(it != sub_peripherals.end());
	return it->second.get();
}

void RendererManager::ondestroy_sub_peripheral(windowID id) {
	auto it = sub_peripherals.find(id);
	if (it == sub_peripherals.end()) {
		return;
	}
	sub_peripherals.erase(it);
}