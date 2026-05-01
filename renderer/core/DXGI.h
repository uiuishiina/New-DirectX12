#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	DXGIクラス
class DXGI final
{
	ComPtr<IDXGIFactory6> factory_;
	ComPtr<IDXGIAdapter4> adapter_;
	
	[[nodiscard]] bool create_factory();

	[[nodiscard]] bool resolve_adapter();

	ComPtr<IDXGIAdapter4> select_adapter(DXGI_GPU_PREFERENCE preference);

public:
	DXGI() = default;
	~DXGI() = default;

	DXGI(const DXGI&) = delete;
	DXGI& operator=(const DXGI&) = delete;
	DXGI(const DXGI&&) = delete;
	DXGI&& operator=(const DXGI&&) = delete;

	[[nodiscard]] bool initialize_DXGI();

	[[nodiscard]] IDXGIFactory6* get_factory() const noexcept;

	[[nodiscard]] IDXGIAdapter4* get_adapter() const noexcept;
};