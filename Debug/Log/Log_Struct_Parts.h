#pragma once
//ログ構造体に使うパーツ
#include<string>
#include<string_view>
#include<vector>
#include<unordered_map>

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<sstream>

namespace Log
{
	//ログのレベル
	namespace Level
	{
		//レベルの種類
		enum struct Level
		{
			Info, Warning, Error
		};
		//レベルがエラーかどうかを判定する関数
		constexpr bool is_error(Level l)
		{
			return l == Level::Error;
		}
		//レベルを文字列に変換する関数
		constexpr std::string_view to_string(Level l) {
			switch (l) {
			case Level::Info: return "Info";
			case Level::Warning: return "Warning";
			case Level::Error: return "Error";
			default: return "";
			}
		}
	}

	namespace Message
	{
		inline std::string message_templete(const std::string& value) {
			return value;
		}

		inline std::string message_templete(const char* value) {
			return value ? std::string(value) : "";
		}

		inline std::string message_templete(HRESULT value) {
			char* msgBuf = nullptr;
			FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				value,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPSTR)&msgBuf,
				0,
				NULL
			);
			std::string result = "hr = " + std::to_string(value) + " : " + (msgBuf ? msgBuf : "Unknown error");
			if (msgBuf) LocalFree(msgBuf);
			return result;
		}

		template<typename T>
		inline std::string message_templete(T* value) {
			std::ostringstream oss;
			oss << value;
			return oss.str();
		}

		template <typename T>
		inline std::string message_templete(const T& value) {
			std::ostringstream oss;
			oss << value;
			return oss.str();
		}
	};

	//ログごとのヘッダー
	namespace Header
	{
		//---------------------------------------------------------------------------------------------------
		//ヘッダーの種類
		enum struct Type
		{
			File, Line, Func, Value, Message, end
		};
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		//ヘッダーの種類を文字列に変換するための配列
		constexpr std::string_view TypeString[] = {
			"File","Line","Func","Value","Message"
		};
		//ヘッダー文字列変換関数
		constexpr std::string_view to_string(Type h)
		{
			auto idx = static_cast<std::size_t>(h);
			return idx < static_cast<std::size_t>(Type::end) ? TypeString[idx] : "";
		}
		//ヘッダーの種類が有効かどうかを判定する関数
		constexpr bool is_valid(Type h)
		{
			auto idx = static_cast<std::size_t>(h);
			return idx < static_cast<std::size_t>(Type::end);
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------

		//ヘッダー構造体...入力されたデータを識別するための構造体。最終的にはRecordのヘッダーマップに変換される
		class Header {
			Type type;	//ヘッダーの種類
			std::string value;	//ヘッダーの値
		public:
			//コンストラクタ
			Header() = delete;	//デフォルトコンストラクタは削除
			template<typename T>
			Header(Type t, const T& v) : type(t), value(Message::message_templete(v)) {}	//種類と値を指定して初期化

			constexpr Type get_type() const { return type; }
			const std::string& get_value() const { return value; }
		};

		//---------------------------------------------------------------------------------------------------
	}

	//ログのレコード構造体
	class Record {
		//---------------------------------------------------------------------------------------------------
		Level::Level level;	//ログのレベル
		std::unordered_map<Header::Type, std::string> headers;	//ヘッダーの種類と値のマップ
		std::vector<std::string> messages;	//メッセージのリスト
		//---------------------------------------------------------------------------------------------------
	public:
		//コンストラクタ
		Record() = delete;	//デフォルトコンストラクタは削除
		Record(Level::Level l) : level(l) {};	//レベルを指定して初期化

		//---------------------------------------------------------------------------------------------------
		//レベルを取得する関数
		Level::Level get_level() const { return level; }

		//ヘッダーを取得する関数
		const std::unordered_map<Header::Type, std::string>& get_headers() const { return headers; }

		//メッセージを取得する関数
		const std::vector<std::string>& get_messages() const { return messages; }
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		//ヘッダーとメッセージを追加する関数
		void Add_header(Header::Type type, const std::string& value) {
			headers.try_emplace(type, value);	//同じヘッダーの種類が存在しない場合に追加
		}

		void Add_message(const std::string& message) {
			messages.push_back(message);	//メッセージを追加
		}
		//---------------------------------------------------------------------------------------------------
	};
};