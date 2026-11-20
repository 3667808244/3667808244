#pragma once

#include <expected>
#include <memory>
#include <string_view>

namespace ezml::error {
	enum class Error {	// 错误码定义
		FileNotFound,
		MalformedData,
		//...
		// 音频
		AudioDeviceUnavailable,	 // 无法打开音频输出设备
		UnsupportedAudioFormat,	 // 不支持的音频编码或格式
	};

	std::string_view to_string_view(Error error);

	/* 返回值约定
	 * - 有真实失败路径的操作返回 Result<T> 或 Status，失败时带回 Error
	 * - 没有失败路径的操作返回 void，不为了形式统一而硬套 Status
	 * - 库里的类型都是可移动的轻量句柄，默认按值返回，不必为了"避免拷贝"再套一层 unique_ptr
	 * */

	// 按值返回的结果：工厂与"产生新对象"的操作的默认形式
	template <typename T>
	using Result = std::expected<T, Error>;

	// 无值结果：只有成败、没有产物的操作(打开、播放)
	using Status = std::expected<void, Error>;

	// 堆结果：仅当调用点拿不到 T 的完整定义、或 T 大到不宜放进 expected 时才用
	template <typename T>
	using Boxed = std::expected<std::unique_ptr<T>, Error>;
}  // namespace ezml::error
