#pragma once
//	Assert.h
#include <type_traits>
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>


namespace Assert
{
	namespace Policy
	{
		template <typename T>
		struct AssertPolicy {
			static bool check(const T& value) {
				return static_cast<bool>(value);
			}
		};

		template <>
		struct AssertPolicy<bool> {
			static bool check(bool value) {
				return value;
			}
		};

		template <typename T>
		struct AssertPolicy<T*> {
			static bool check(T* value) {
				return value != nullptr;
			}
		};

		template <>
		struct AssertPolicy<HRESULT> {
			static bool check(HRESULT value) {
				return SUCCEEDED(value);
			}
		};


	}

	class Assert final
	{
	public:
		Assert() = default;
		~Assert() = default;
		Assert(const Assert&) = delete;
		Assert& operator=(const Assert&) = delete;
		Assert(Assert&&) = delete;
		Assert& operator=(Assert&&) = delete;

		void initialize() {
			//初期化処理が必要な場合はここに記述
		}

		// チェック関数...値が条件を満たしているかどうかを判定する関数
		template<typename T>
		[[nodiscard]] bool policy_check(const T& value) {
			return Policy::AssertPolicy<T>::check(value);
		}
	};
}

