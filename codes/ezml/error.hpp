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

	template <typename T>
	using Result = std::expected<std::unique_ptr<T>, Error>;

	// 按值返回的结果，用于不依赖堆所有权的工厂
	template <typename T>
	using ValueResult = std::expected<T, Error>;
}  // namespace ezml::error