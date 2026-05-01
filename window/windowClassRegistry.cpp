#include"windowClassRegistry.h"
#include"../Debug/Debug.h"

[[nodiscard]] bool windowClassRegistry::register_class(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc) {

	if (class_map.find(name) != class_map.end()) {
		LOG_WARNING(LOG_HEADER(Message, "Alrady register"));
		return false;
	}

	WNDCLASSEX wc;
	std::memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = name;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	if (!RegisterClassEx(&wc)) {
		DWORD dwError = GetLastError();
		LOG_WARNING(LOG_HEADER(Message, "RegisterClassEx failed." + std::to_string(dwError)));
		return false;
	}

	class_map.emplace(name, wc);
	return true;
}

[[nodiscard]] WNDCLASSEX windowClassRegistry::get_class(const wchar_t* name)const noexcept {

	auto it = class_map.find(name);
	ASSERT(it != class_map.end());
	return it->second;
}