#pragma once
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<unordered_map>

class windowClassRegistry final
{
	std::unordered_map<const wchar_t*, WNDCLASSEX> class_map{};
public:
	windowClassRegistry() = default;
	~windowClassRegistry() = default;

	windowClassRegistry(const windowClassRegistry&) = delete;
	windowClassRegistry& operator=(const windowClassRegistry&) = delete;
	windowClassRegistry(const windowClassRegistry&&) = delete;
	windowClassRegistry& operator=(const windowClassRegistry&&) = delete;

	[[nodiscard]] bool register_class(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);

	[[nodiscard]] WNDCLASSEX get_class(const wchar_t* name)const noexcept;
};