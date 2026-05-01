#pragma once
#include"LoggerBase.h"
#include"DebugWindow_Logger.h"
#include"Console_Logger.h"
#include<memory>
#include<vector>

//ロガーマネージャークラス
class LoggerManager final
{
	std::vector<std::unique_ptr<LoggerBase>> loggers;	//ロガーのリスト
public:
	LoggerManager() = default;
	~LoggerManager() = default;
	LoggerManager(const LoggerManager&) = delete;
	LoggerManager& operator=(const LoggerManager&) = delete;
	LoggerManager(LoggerManager&&) = delete;
	LoggerManager& operator=(LoggerManager&&) = delete;

	//初期化関数
	void Initialize()
	{
		loggers.push_back(std::make_unique<DebugWindow_Logger>());	//デバッグウィンドウロガーを追加
		// loggers.push_back(std::make_unique<Console_Logger>());	//デバッグウィンドウロガーを追加
		for (const auto& logger : loggers) {
			logger->Initialize();	//各ロガーを初期化
		}
	}

	//ログを各ロガーに送信する関数
	void SendLog(const Log::Record& record)
	{
		for (const auto& logger : loggers)
		{
			logger->Log(record);	//各ロガーにログを送信
		}
	}
};