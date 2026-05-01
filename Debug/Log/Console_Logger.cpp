#include"Console_Logger.h"
#include<optional>
#include<Windows.h>
#include<iostream>

namespace Hadder = Log::Header;
using namespace std;

Console_Logger::Console_Logger() {
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
}

//	ログの出力関数の実装
void Console_Logger::output(std::string_view message) {
	cout << message << endl;
}


//指定された長さの区切り線を生成する関数
static std::string Line(int length)
{
	std::string line(50, '=');
	return line;
}

//ヘッダーの種類と値のマップを文字列に変換する関数
static std::optional<std::string> HeaderToString(const std::unordered_map<Hadder::Type, std::string>& headers, Hadder::Type type)
{
	std::string result;
	auto it = headers.find(type);
	if (it == headers.end()) { return std::nullopt; }
	result = "[ " + std::string(Log::Header::to_string(type)) + " ] " + it->second;	//ヘッダーの種類と値を文字列に変換
	return result;
}

//ヘッダーの種類と値を出力メッセージに追加する関数
static void PushHedderMessage(std::vector<std::string>& output_messages, const std::unordered_map<Hadder::Type, std::string>& headers, Hadder::Type type)
{
	if (auto header_str = HeaderToString(headers, type); header_str) {
		output_messages.push_back(*header_str);	//ヘッダーの種類と値を出力メッセージに追加
	}
}

//ログの処理関数の実装
void Console_Logger::Log(const Log::Record& message) {
	//出力するメッセージのリストを作成
	std::vector<std::string> output_messages;	//出力するメッセージのリスト
	//エラーログの場合、区切り線を出力メッセージの先頭と末尾に追加
	if (message.get_level() == Log::Level::Level::Error) {
		auto line = Line(50);
		output_messages.push_back(line);
	}
	//ヘッダーの種類と値を出力メッセージに追加
	{
		const auto& headers = message.get_headers();
		PushHedderMessage(output_messages, headers, Hadder::Type::Func);
		PushHedderMessage(output_messages, headers, Hadder::Type::File);
		PushHedderMessage(output_messages, headers, Hadder::Type::Line);
		PushHedderMessage(output_messages, headers, Hadder::Type::Value);
	}
	//メッセージを出力メッセージに追加
	{
		const auto& messages = message.get_messages();
		for (const auto& msg : messages) {
			output_messages.push_back("[ Message ] " + msg);	//メッセージを出力メッセージに追加
		}
	}
	//エラーログの場合、区切り線を出力メッセージの末尾に追加
	if (message.get_level() == Log::Level::Level::Error) {
		auto line = Line(50);
		output_messages.push_back(line);
	}
	//出力メッセージをログに出力
	for (const auto& msg : output_messages) {
		output(msg);
	}
}
