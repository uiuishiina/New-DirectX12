#pragma once
#pragma once
// Device.h

#include"DXGI.h"

using Microsoft::WRL::ComPtr;

//	D3D12デバイスクラス
class Device final
{
	ComPtr<ID3D12Device> device_;

	[[nodiscard]] ComPtr<ID3D12Device> select_device(IDXGIAdapter4* adapter, D3D_FEATURE_LEVEL featureLevel);
public:
	Device() = default;
	~Device() = default;

	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;
	Device(const Device&&) = delete;
	Device&& operator=(const Device&&) = delete;

	[[nodiscard]] bool create_device(IDXGIAdapter4* adapter);

	[[nodiscard]] ID3D12Device* get_device() const noexcept;
};