#include"Application.h"
#include"../window/window.h"
#include"../Debug/Debug.h"

[[nodiscard]] bool Application::initalize(HINSTANCE hInstance) {

	//main
	
	//liftime
	lifetime_manager = std::make_unique<LifetimeManager>();
	if (!lifetime_manager->initalize(this)) {
		LOG_ERROR(LOG_HEADER(Message, "lifetime_manager failed."));
		return false;
	}

	//window
	window_manager = std::make_unique<windowManager>();

	//Registry
	if (!window_manager->initalize(lifetime_manager.get())) {
		LOG_ERROR(LOG_HEADER(Message, "windowManager failed."));
		return false;
	}

	//main_window
	if (!window_manager->create_main_window(hInstance, 1280, 720)) {
		LOG_ERROR(LOG_HEADER(Message, "create_main_window failed."));
		return false;
	}
	
	//renderer
	renderer_manager = std::make_unique<RendererManager>();

	//renderer_core
	if (!renderer_manager->initalize()) {
		LOG_ERROR(LOG_HEADER(Message, "renderer_manager failed."));
		return false;
	}

	auto main = window_manager->get_mainwindow();

	//renderer_peripheral
	if (!renderer_manager->create_main_peripheral(main)) {
		LOG_ERROR(LOG_HEADER(Message, "renderer_manager failed."));
		return false;
	}

	auto peripheral = renderer_manager->get_main_peripheral();

	auto unit = std::make_unique<RenderUnit>();
	if (!unit->initalize_unit(main, peripheral)) {
		LOG_ERROR(LOG_HEADER(Message, "initalize_unit failed."));
		return false;
	}

	auto id = windowID(window_id++);
	if (!lifetime_manager->submit_unit(id, std::move(unit))) {
		LOG_ERROR(LOG_HEADER(Message, "submit_unit failed."));
		return false;
	}

	LOG_INFO(LOG_HEADER(Message, "initalize clear"));
	return true;
}

[[nodiscard]] bool Application::create_sub(HINSTANCE hInstance) {

	//id
	auto id = windowID(window_id++);

	//window_sub
	if (!window_manager->create_sub_window(hInstance,id, 720, 720)) {
		LOG_ERROR(LOG_HEADER(Message, "create_sub_window failed."));
		return false;
	}
	auto sub = window_manager->get_subwindow(id);

	//peripheral_sub
	if (!renderer_manager->create_sub_peripheral(sub,id)) {
		LOG_ERROR(LOG_HEADER(Message, "renderer_manager failed."));
		return false;
	}
	auto peripheral = renderer_manager->get_sub_peripheral(id);

	//unit
	auto unit = std::make_unique<RenderUnit>();
	if (!unit->initalize_unit(sub, peripheral)) {
		LOG_ERROR(LOG_HEADER(Message, "initalize_unit failed."));
		return false;
	}
	
	if (!lifetime_manager->submit_unit(id, std::move(unit))) {
		LOG_ERROR(LOG_HEADER(Message, "submit_unit failed."));
		return false;
	}

	return true;
}

void Application::run_App() {
	while (window_manager->message_loop()) {

		lifetime_manager->update();
	}
	end_App();
}

void Application::end_App() {
	lifetime_manager->end();
}

void Application::ondestroy_window(windowID id) {
	window_manager->ondestroy_window(id);
	renderer_manager->ondestroy_sub_peripheral(id);
}