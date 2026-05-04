#pragma once
#include"RendererPeripheral.h"

class Peripheral_polygon final : public RendererPeripheral
{
public:
	Peripheral_polygon();
	~Peripheral_polygon();

	Peripheral_polygon(const Peripheral_polygon&) = delete;
	Peripheral_polygon& operator=(const Peripheral_polygon&) = delete;
	Peripheral_polygon(const Peripheral_polygon&&) = delete;
	Peripheral_polygon& operator=(const Peripheral_polygon&&) = delete;

	[[nodiscard]] bool initalize(RendererCore* core, windowBase* window, const int& buffercount)override;

	void update()override;

	void end()override;
};