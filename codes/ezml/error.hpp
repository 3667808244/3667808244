#pragma once

#include <expected>
#include <memory>
#include <string_view>

namespace ezml::error {
	enum class Error {	// 错误码定义
		FileNotFound,
		MalformedData,
		//...
	};

	std::string_view to_string_view(Error error);

	template <typename T>
	using Result = std::expected<std::unique_ptr<T>, Error>;
}  // namespace ezml::error