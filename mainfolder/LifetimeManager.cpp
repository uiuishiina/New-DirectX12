#include"LifetimeManager.h"
#include"../window/window.h"

#include"Application.h"
#include"../Debug/Debug.h"

LifetimeManager::LifetimeManager() = default;
LifetimeManager::~LifetimeManager() = default;

[[nodiscard]] bool LifetimeManager::initalize(Application* app) {
	app_ = app;

	return true;
}

[[nodiscard]] bool LifetimeManager::submit_unit(windowID id, std::unique_ptr<RenderUnit> unit) {
	if (unit_map.find(id) != unit_map.end()) {
		return false;
	}

	auto hwnd = unit->get_window()->get_hwnd();
	id_map.emplace(hwnd, id);
	unit_map.emplace(id, std::move(unit));

	return true;
}

void LifetimeManager::ondestroy_unit(HWND hwnd) {
	auto it = id_map.find(hwnd);
	if (it == id_map.end()) {
		return;
	}
	LOG_INFO(LOG_HEADER(Message, "call ondestroy_unit"));

	auto id = it->second;
	ondestroy_vec.push_back(id);
	
	id_map.erase(it);
	unit_map.erase(id);
}

void LifetimeManager::update() {

	if (!ondestroy_vec.empty()) {
		for (auto& p : ondestroy_vec) {
			app_->ondestroy_window(p);
		}
	}

	for (auto& p : unit_map) {
		p.second->update();
	}
}

void LifetimeManager::end() {

}