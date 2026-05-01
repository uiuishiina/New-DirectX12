#include"Application.h"
#include"../window/window.h"
#include"../Debug/Debug.h"

[[nodiscard]] bool Application::initalize(HINSTANCE hInstance) {

	window_manager = std::make_unique<windowManager>();
	if (!window_manager->initalize()) {
		LOG_ERROR(LOG_HEADER(Message, "windowManager failed."));
		return false;
	}
	if (!window_manager->create_main_window(hInstance, 1280, 720)) {
		LOG_ERROR(LOG_HEADER(Message, "create_main_window failed."));
		return false;
	}
	//if (!window_manager->create_sub_window(hInstance, 720, 720)) {
	//	LOG_ERROR(LOG_HEADER(Message, "create_sub_window failed."));
	//	return false;
	//}

	renderer_manager = std::make_unique<RendererManager>();
	if (!renderer_manager->initalize()) {
		LOG_ERROR(LOG_HEADER(Message, "renderer_manager failed."));
		return false;
	}

	windowContext context;
	context.hwnd = window_manager->get_mainwindow()->get_hwnd();
	context.size = window_manager->get_mainwindow()->get_size();
	if (!renderer_manager->create_peripheral(context)) {
		LOG_ERROR(LOG_HEADER(Message, "renderer_manager failed."));
		return false;
	}

	return true;
}

void Application::run_App() {
	while (window_manager->message_loop()) {

		renderer_manager->update();
	}
	end_App();
}

void Application::end_App() {

}