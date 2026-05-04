#pragma once
#include"../renderer/core/RendererCore.h"
#include"../mainfolder/peripheral/RendererPeripheral.h"
#include"../mainfolder/peripheral/Peripheral_polygon.h"
#include"ID.h"
#include<memory>
#include<unordered_map>

class windowBase;

class RendererManager final
{
	std::unique_ptr<RendererCore> renderer_core{};
	std::unique_ptr<RendererPeripheral> main_peripheral{};
	std::unordered_map<windowID,std::unique_ptr<RendererPeripheral>> sub_peripherals{};
public:
	RendererManager();
	~RendererManager();

	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
	RendererManager(const RendererManager&&) = delete;
	RendererManager& operator=(const RendererManager&&) = delete;

	[[nodiscard]] bool initalize();

	[[nodiscard]] bool create_main_peripheral(windowBase* window);

	[[nodiscard]] bool create_sub_peripheral(windowBase* window, windowID id);

	[[nodiscard]] RendererPeripheral* get_main_peripheral();

	[[nodiscard]] RendererPeripheral* get_sub_peripheral(windowID id);

	void ondestroy_sub_peripheral(windowID id);
};