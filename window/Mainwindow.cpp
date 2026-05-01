#include"Mainwindow.h"
#include"../mainfolder/windowManager.h"
#include"windowClassRegistry.h"
#include"../Debug/Debug.h"

namespace {
	const wchar_t* const class_name = L"main_window";
}

LRESULT Mainwindow::window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

[[nodiscard]] bool Mainwindow::create_window(HINSTANCE hInstance, uint16_t width, uint16_t height) {

	if (!window_manager) {
		return false;
	}

	if (!window_manager->get_registry()->register_class(hInstance, class_name, windowBase::StaticWindowProc)) {
		return false;
	}
	
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

	//	ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);

	return true;
}