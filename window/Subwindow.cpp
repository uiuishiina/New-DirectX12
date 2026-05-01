#include"Subwindow.h"
#include"../mainfolder/windowManager.h"
#include"windowClassRegistry.h"
#include"../Debug/Debug.h"

namespace {
	const wchar_t* const class_name = L"sub_window";
}

LRESULT Subwindow::window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
	{
		auto self = (Subwindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		self->hwnd_ = nullptr;
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

[[nodiscard]] bool Subwindow::create_window(HINSTANCE hInstance, uint16_t width, uint16_t height) {

	if (!window_manager) {
		return false;
	}

	LOG_INFO(LOG_VALUE(window_manager->get_registry()->register_class(hInstance, class_name, windowBase::StaticWindowProc)));

	auto wc = window_manager->get_registry()->get_class(class_name);
	//	ウィンドウ作成
	hwnd_ = CreateWindowEx(
		0,						//	拡張スタイル
		wc.lpszClassName,		//	クラス名
		wc.lpszClassName,		//	ウィンドウタイトル
		WS_OVERLAPPEDWINDOW,	//	ウィンドウスタイル
		CW_USEDEFAULT, CW_USEDEFAULT, //	位置とサイズ
		width, height,
		nullptr,				//	親ウィンドウ
		nullptr,				//	メニューハンドル
		hInstance,				//	インスタンスハンドル
		this					//	追加パラメータ
	);

	if (!hwnd_) {
		return false;
	}

	window_size_ = { width, height };

	//	ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);

	return true;
}