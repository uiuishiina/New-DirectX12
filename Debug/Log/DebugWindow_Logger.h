#pragma once
#include"LoggerBase.h"

class DebugWindow_Logger final : public LoggerBase
{
protected:
	//	ログの出力関数の実装
	void output(std::string_view message) override;
public:
	DebugWindow_Logger() = default;
	~DebugWindow_Logger() = default;
	DebugWindow_Logger(const DebugWindow_Logger&) = delete;
	DebugWindow_Logger& operator=(const DebugWindow_Logger&) = delete;
	DebugWindow_Logger(DebugWindow_Logger&&) = delete;
	DebugWindow_Logger& operator=(DebugWindow_Logger&&) = delete;

	//ログの処理関数の実装
	void Log(const Log::Record& message) override;
};