#pragma once
#include"Log_pipline.h"

#define LOG_HEADER(type, value) Log::Header::Header(Log::Header::Type::type, value)	//ログヘッダーマクロ
#define LOG_CONTEXT()  Log::Header::Header(Log::Header::Type::Func, __func__),Log::Header::Header(Log::Header::Type::File, __FILE__), Log::Header::Header(Log::Header::Type::Line, std::to_string(__LINE__))	//ログコンテキストマクロ

#define log_value(expr) (std::string(#expr) + "  =  " + std::to_string(expr))
#define LOG_VALUE(expr) Log::Header::Header(Log::Header::Type::Value, log_value(expr))

#define LOG_INFO(...)	LogPipeline::GetInstance().Process(Log::Level::Level::Info, __VA_ARGS__)
#define LOG_WARNING(...) LogPipeline::GetInstance().Process(Log::Level::Level::Warning, __VA_ARGS__)
#define LOG_ERROR(...)	LogPipeline::GetInstance().Process(Log::Level::Level::Error, __VA_ARGS__)
