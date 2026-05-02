#pragma once
#include"RenderUnit.h"
#include"ID.h"
#include<unordered_map>
#include<memory>
#include<vector>

class RenderUnit;

struct HWND__;
using HWND = HWND__*;

class Application;

class LifetimeManager final
{
	Application* app_{};
	std::unordered_map<HWND, windowID> id_map{};
	std::unordered_map<windowID, std::unique_ptr<RenderUnit>> unit_map{};
	std::vector<windowID> ondestroy_vec{};
public:
	LifetimeManager();
	~LifetimeManager();

	LifetimeManager(const LifetimeManager&) = delete;
	LifetimeManager& operator= (const LifetimeManager&) = delete;
	LifetimeManager(const LifetimeManager&&) = delete;
	LifetimeManager& operator= (const LifetimeManager&&) = delete;

	[[nodiscard]] bool initalize(Application* app);

	[[nodiscard]] bool submit_unit(windowID id, std::unique_ptr<RenderUnit> unit);

	void update();

	void ondestroy_unit(HWND hwnd);

	void end();
};