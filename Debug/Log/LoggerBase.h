#pragma once
#include"Log_Struct_Parts.h"

//ロガーの基底クラス
class LoggerBase
{
protected:
	virtual void output(std::string_view message) = 0;	//ログの出力関数（純粋仮想関数）
public:
	LoggerBase() = default;
	virtual ~LoggerBase() = default;
	LoggerBase(const LoggerBase&) = delete;
	LoggerBase& operator=(const LoggerBase&) = delete;
	LoggerBase(LoggerBase&&) = delete;
	LoggerBase& operator=(LoggerBase&&) = delete;

	virtual void Initialize() {}	//初期化関数（必要に応じてオーバーライド可能）

	virtual void Log(const Log::Record& message) = 0;	//純粋仮想関数
};