#include"../Debug/Debug.h"
#include"../window/windowClassRegistry.h"
#include"../window/window.h"
#include"../window/Mainwindow.h"
#include"../window/Subwindow.h"
#include"windowManager.h"

windowManager::windowManager() {
	initalize();
}
windowManager::~windowManager() = default;

#define CHECK(expr) \
    if (!(expr)) { \
        LOG_ERROR(LOG_CONTEXT(), LOG_HEADER(Message,#expr)); \
        return false; \
    }

bool windowManager::initalize() {
	registry = std::make_unique<windowClassRegistry>();

	return true;
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool windowManager::create_main_window(HINSTANCE hInstance, const uint16_t& width, const uint16_t height) {
	
	main_window = std::make_unique<Mainwindow>(this);
	CHECK(main_window->create_window(hInstance, width, height));

	return true;
}

[[nodiscard]] windowBase* windowManager::get_mainwindow()const noexcept {
	ASSERT(main_window);
	return main_window.get();
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool windowManager::create_sub_window(HINSTANCE hInstance, const uint16_t& width, const uint16_t height) {
	
	for (int i = 0; i < 2; i++) {
		std::unique_ptr sub = std::make_unique<Subwindow>(this);
		CHECK(sub->create_window(hInstance, width, height));

		sub_window.emplace_back(std::move(sub));
	}

	return true;
}

[[nodiscard]] windowBase* windowManager::get_subwindow(size_t index)const noexcept {
	ASSERT(sub_window.size() < index);
	ASSERT(sub_window[index]);
	return sub_window[index].get();
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