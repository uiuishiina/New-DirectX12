#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include"Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	Application App;
	if (!App.initalize(hInstance)) {
		return -1;
	}
	if (!App.create_sub(hInstance)) {
		return -1;
	}
	if (!App.create_sub(hInstance)) {
		return -1;
	}
	App.run_App();
	return 0;
}