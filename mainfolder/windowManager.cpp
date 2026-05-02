#include"../Debug/Debug.h"
#include"../window/windowClassRegistry.h"
#include"../window/window.h"
#include"../window/Mainwindow.h"
#include"../window/Subwindow.h"
#include"windowManager.h"
#include"LifetimeManager.h"

windowManager::windowManager() = default;
windowManager::~windowManager() = default;

#define CHECK(expr) \
    if (!(expr)) { \
        LOG_ERROR(LOG_CONTEXT(), LOG_HEADER(Message,#expr)); \
        return false; \
    }

[[nodiscard]] bool windowManager::initalize(LifetimeManager * life) {
	registry = std::make_unique<windowClassRegistry>();
	life_ = life;
	return true;
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool windowManager::create_main_window(HINSTANCE hInstance, const uint16_t& width, const uint16_t height) {
	
	main_window = std::make_unique<Mainwindow>(this, life_);
	CHECK(main_window->create_window(hInstance, width, height));

	return true;
}

[[nodiscard]] windowBase* windowManager::get_mainwindow()const noexcept {
	ASSERT(main_window);
	return main_window.get();
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool windowManager::create_sub_window(HINSTANCE hInstance, windowID id, const uint16_t& width, const uint16_t height) {

	std::unique_ptr sub = std::make_unique<Subwindow>(this, life_);
	CHECK(sub->create_window(hInstance, width, height));
	sub_window.emplace(id,std::move(sub));

	return true;
}

[[nodiscard]] windowBase* windowManager::get_subwindow(windowID id)const noexcept {
	ASSERT(!sub_window.empty());
	auto it = sub_window.find(id);
	ASSERT(it != sub_window.end());
	return it->second.get();
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool windowManager::message_loop() {

	MSG msg_{};
	while (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE)) {
		if (msg_.message == WM_QUIT) {
			return false;
		}
		// メッセージ処理
		TranslateMessage(&msg_);
		DispatchMessage(&msg_);
	}

	return true;
}

[[nodiscard]] windowClassRegistry* windowManager::get_registry()const noexcept {
	ASSERT(registry);
	return registry.get();
}

void windowManager::ondestroy_window(windowID id) {

	auto it = sub_window.find(id);
	if (it == sub_window.end()) {
		return;
	}
	LOG_INFO(LOG_HEADER(Message, "ondestroy_window"));
	sub_window.erase(it);
}