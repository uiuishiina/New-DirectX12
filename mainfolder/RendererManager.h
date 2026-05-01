#pragma once
#include"../renderer/core/RendererCore.h"
#include"../renderer/peripheral/RendererPeripheral.h"
#include<memory>

//class RendererCore;
//class RendererPeripheral;

class RendererManager final
{
	std::unique_ptr<RendererCore> renderer_core{};
	std::unique_ptr<RendererPeripheral> renderer_peripheral{};
public:
	RendererManager();
	~RendererManager();

	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
	RendererManager(const RendererManager&&) = delete;
	RendererManager& operator=(const RendererManager&&) = delete;

	[[nodiscard]] bool initalize();

	[[nodiscard]] bool create_peripheral(windowContext& contest);

	void update();
};