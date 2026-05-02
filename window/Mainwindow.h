#pragma once
#include"window.h"

class Mainwindow final : public windowBase
{
	LRESULT window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
public:
	Mainwindow() = delete;
	Mainwindow(windowManager* manager,LifetimeManager* life) :windowBase(manager,life) {};
	~Mainwindow() = default;

	Mainwindow(const Mainwindow&) = delete;
	Mainwindow& operator=(const Mainwindow&) = delete;
	Mainwindow(const Mainwindow&&) = delete;
	Mainwindow& operator=(const Mainwindow&&) = delete;

	[[nodiscard]] bool create_window(HINSTANCE hInstance, uint16_t width, uint16_t height)override;
};