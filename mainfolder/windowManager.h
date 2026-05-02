#pragma once
#include"ID.h"
#include<memory>
#include<unordered_map>

//	前方宣言
class windowBase;
class windowClassRegistry;
class LifetimeManager;

struct HWND__;
using HWND = HWND__*;

struct HINSTANCE__;
using HINSTANCE = HINSTANCE__*;

class windowManager final
{
	LifetimeManager* life_{};
	std::unique_ptr<windowClassRegistry>		registry{};
	std::unique_ptr<windowBase>					main_window{};
	std::unordered_map<windowID,std::unique_ptr<windowBase>>	sub_window{};
public:
	windowManager();
	~windowManager();

	windowManager(const windowManager&) = delete;
	windowManager& operator= (const windowManager&) = delete;
	windowManager(const windowManager&&) = delete;
	windowManager& operator= (const windowManager&&) = delete;

	[[nodiscard]] bool initalize(LifetimeManager* life);

	[[nodiscard]] bool create_main_window(HINSTANCE hInstance, const uint16_t& width, const uint16_t height);

	[[nodiscard]] windowBase* get_mainwindow()const noexcept;

	[[nodiscard]] bool create_sub_window(HINSTANCE hInstance, windowID id, const uint16_t& width, const uint16_t height);

	[[nodiscard]] windowBase* get_subwindow(windowID id)const noexcept;

	[[nodiscard]] bool message_loop();

	[[nodiscard]] windowClassRegistry* get_registry()const noexcept;

	void ondestroy_window(windowID id);
};