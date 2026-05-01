#pragma once
#include<concepts>
#include"Log_Struct_Parts.h"

//ログ構造体のパーツの概念
template<typename T>
concept Log_Struct_Parts = std::is_same_v<T, Log::Header::Header>;

//ログビルダークラス
class LogBuilder final
{
public:
	//シングルトンの実装
	LogBuilder() = default;
	~LogBuilder() = default;
	LogBuilder(const LogBuilder&) = delete;
	LogBuilder& operator=(const LogBuilder&) = delete;
	LogBuilder(LogBuilder&&) = delete;
	LogBuilder& operator=(LogBuilder&&) = delete;

	//ログ構造体のビルド関数
	template<Log_Struct_Parts... Args>
	Log::Record BuildLog(Log::Level::Level level,Args... args)
	{
		Log::Record record(level);	//ログ構造体をレベルで初期化
		//引数を展開してログ構造体に追加
		//引数を展開して、ヘッダーの種類がMessageの場合はメッセージとして追加し、それ以外の場合はヘッダーとして追加
		(((args.get_type() == Log::Header::Type::Message) ? 
			record.Add_message(args.get_value()) : record.Add_header(args.get_type(), args.get_value())), ...);
		return record;
	}
};