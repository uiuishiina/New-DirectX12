#pragma once
#include"window.h"

class Subwindow final : public windowBase
{
	LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	void ondestory_window(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)override;
public:
	Subwindow() = delete;
	Subwindow(windowManager* manager, LifetimeManager* life) :windowBase(manager,life) {};
	~Subwindow() = default;

	Subwindow(const Subwindow&) = delete;
	Subwindow& operator=(const Subwindow&) = delete;
	Subwindow(const Subwindow&&) = delete;
	Subwindow& operator=(const Subwindow&&) = delete;

	[[nodiscard]] bool create_window(HINSTANCE hInstance, uint16_t width, uint16_t height)override;
};