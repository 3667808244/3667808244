#pragma once

#include <filesystem>
#include <string_view>

#include "ezml/error.hpp"
#include "ezml/surface.hpp"
#include "ezml/types.hpp"
#include "types.hpp"

namespace ezml::font {
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

			error::Result<surface::Surface> render(std::string_view string, float size, types::RgbaColor frontground,
												   types::RgbaColor background = { 0, 0, 0, 0 });

			static error::Result<Font> load_file(const std::filesystem::path &path);
	};
}  // namespace ezml::font
