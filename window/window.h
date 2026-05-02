#pragma once

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<memory>

class windowManager;
class LifetimeManager;

class windowBase
{
protected:
	HWND hwnd_{};
	std::pair<uint16_t, uint16_t> window_size_{};
	windowManager* window_manager = nullptr;
	LifetimeManager* lifetime_manager = nullptr;
	
	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual void ondestory_window(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {};
public:
	windowBase() = delete;
	explicit windowBase(windowManager* window, LifetimeManager* life) :window_manager(window), lifetime_manager(life){};
	virtual ~windowBase() = default;

	windowBase(const windowBase&) = delete;
	windowBase& operator=(const windowBase&) = delete;
	windowBase(const windowBase&&) = delete;
	windowBase& operator=(const windowBase&&) = delete;
	
	[[nodiscard]] virtual bool create_window(HINSTANCE hInstance, uint16_t width, uint16_t height) = 0;

	[[nodiscard]] HWND get_hwnd()const noexcept;

	[[nodiscard]] std::pair<uint16_t, uint16_t> get_size()const noexcept;
};