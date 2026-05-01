#pragma once
#include"LoggerBase.h"

class Console_Logger final : public LoggerBase
{
protected:
	//	ログの出力関数の実装
	void output(std::string_view message) override;
public:
	Console_Logger();
	~Console_Logger() = default;
	Console_Logger(const Console_Logger&) = delete;
	Console_Logger& operator=(const Console_Logger&) = delete;
	Console_Logger(Console_Logger&&) = delete;
	Console_Logger& operator=(Console_Logger&&) = delete;

	//ログの処理関数の実装
	void Log(const Log::Record& message) override;
};