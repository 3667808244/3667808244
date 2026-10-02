#pragma once

#include <filesystem>
#include <string_view>

#include "ezml/surface.hpp"
#include "ezml/types.hpp"
#include "types.hpp"

namespace ezml {
	namespace font {
		class Font {
				/* 表示一个字体
				 * */
			protected:
				Font(std::filesystem::path &path);

			public:
				Font(const Font &w) = delete;
				Font operator=(const Font &w) = delete;

				Font(Font &&w);
				Font operator=(Font &&w);

				types::Result<surface::Surface> render(std::string_view string);

				static types::Result<Font> load_file(std::filesystem::path &path);
		};
	}  // namespace font
}  // namespace ezml
