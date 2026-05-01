#pragma once
#include"windowManager.h"
#include"RendererManager.h"

class windowManager;
class RendererManager;

class Application final
{
	std::unique_ptr<windowManager> window_manager{};
	std::unique_ptr<RendererManager> renderer_manager{};

	void end_App();
public:
	[[nodiscard]] bool initalize(HINSTANCE hInstance);

	void run_App();
};