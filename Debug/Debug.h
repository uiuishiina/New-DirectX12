#pragma once
//	Debug.h

#include"Log/Log_pipline.h"
#include"Assert/Assert.h"

#define LOG_HEADER(type, value) Log::Header::Header(Log::Header::Type::type, value)	//ログヘッダーマクロ
#define LOG_CONTEXT()  Log::Header::Header(Log::Header::Type::Func, __func__),Log::Header::Header(Log::Header::Type::File, __FILE__), Log::Header::Header(Log::Header::Type::Line, std::to_string(__LINE__))	//ログコンテキストマクロ

#define LOG_VALUE(expr) Log::Header::Header(Log::Header::Type::Value, expr)

#define LOG_INFO(...)	Debug::GetInstance().GetLogPipeline().Process(Log::Level::Level::Info, __VA_ARGS__)
#define LOG_WARNING(...)	Debug::GetInstance().GetLogPipeline().Process(Log::Level::Level::Warning, __VA_ARGS__)
#define LOG_ERROR(...)	Debug::GetInstance().GetLogPipeline().Process(Log::Level::Level::Error, __VA_ARGS__)
#define ASSERT(expr) \
	do { \
	if (!Debug::GetInstance().GetAssert().policy_check(expr)) { \
		LOG_ERROR(LOG_CONTEXT(), LOG_VALUE(expr), LOG_HEADER(Message,#expr)); \
		std::abort();\
	} \
} while(0)

class Debug final
{
	Assert::Assert assert;	//アサートクラスのインスタンス
	LogPipeline log_pipeline;	//ログパイプラインクラスのインスタンス

	Debug() {
		initialize();
	}

	~Debug() = default;
	Debug(const Debug&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(Debug&&) = delete;

	//初期化関数
	void initialize() {
		log_pipeline.Initialize();
		assert.initialize();
	}
public:
	static Debug& GetInstance() {
		static Debug instance;
		return instance;
	}

	Assert::Assert& GetAssert() {
		return assert;
	}

	LogPipeline& GetLogPipeline() {
		return log_pipeline;
	}
};