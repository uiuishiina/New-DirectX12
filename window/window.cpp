#include"window.h"
#include"../Debug/Debug.h"

LRESULT CALLBACK windowBase::StaticWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_NCCREATE) {
		auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		auto pWnd = reinterpret_cast<windowBase*>(cs->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		pWnd->hwnd_ = hwnd;

		return pWnd->window_proc(hwnd, msg, wParam, lParam);
	}

	auto pWnd = reinterpret_cast<windowBase*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (pWnd) {
		return pWnd->window_proc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

[[nodiscard]] HWND windowBase::get_hwnd()const noexcept {
	ASSERT(hwnd_);
	return hwnd_;
}

[[nodiscard]] std::pair<uint16_t, uint16_t> windowBase::get_size()const noexcept {
	ASSERT(hwnd_);
	return window_size_;
}