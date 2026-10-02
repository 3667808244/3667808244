#pragma once

#include <cstdint>
#include <expected>
#include <memory>

namespace ezml {
	namespace types {
		template <typename T>
		struct Vec2 {
				T x, y;
		};

		using Vec2i = Vec2<std::int64_t>;
		using Vec2u = Vec2<std::uint64_t>;
		using Vec2f = Vec2<float>;

		using Pos2 = Vec2f;
		using Size2 = Vec2f;
		using Offset2 = Vec2f;
		using WinSize = Vec2u;

		struct Rect {
				Pos2 pos;
				Size2 size;
		};

		using Radius = float;

		struct RgbaColor {
				uint8_t r, g, b, a;
		};

		struct RgbColor {
				uint8_t r, g, b;
		};

		enum class Error {	// 错误码定义
			FileNotFound,
			//...
		};

		template <typename T>
		using Result = std::expected<std::unique_ptr<T>, Error>;

	}  // namespace types
}  // namespace ezml
