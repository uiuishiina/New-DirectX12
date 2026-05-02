#pragma once
#include"windowManager.h"
#include"RendererManager.h"
#include"LifetimeManager.h"
#include"RenderUnit.h"

#include<unordered_map>

class Application final
{
	std::unique_ptr<windowManager> window_manager{};
	std::unique_ptr<RendererManager> renderer_manager{};
	std::unique_ptr<LifetimeManager> lifetime_manager{};

	int window_id{};

	void end_App();
public:
	[[nodiscard]] bool initalize(HINSTANCE hInstance);

	[[nodiscard]] bool create_sub(HINSTANCE hInstance);

	void run_App();

	void ondestroy_window(windowID id);
};