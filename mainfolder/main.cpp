#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include"windowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	windowManager windowmanager;
	windowmanager.create_main_window(hInstance, 1280, 720);
	while (windowmanager.message_loop()) {

	}
	return 0;
}