#pragma once

#include <filesystem>

#include "ezml/error.hpp"
#include "ezml/math.hpp"
#include "ezml/types.hpp"

namespace ezml::surface {
	class Surface {
			/* 表示一个抽象的绘制目标
			 * */
		protected:
			Surface(types::Size2 size);

		public:
			Surface(const Surface &w) = delete;
			Surface operator=(const Surface &w) = delete;

			Surface(Surface &&w);
			Surface &operator=(Surface &&w);

			void draw_px(types::Pos2 pos, types::RgbaColor color);

			void draw_line(types::Pos2 p1, types::Pos2 p2, types::RgbaColor color, float width = 1.0f);

			void draw_rect(types::Rect, types::RgbaColor color);

			void draw_triangle(types::Pos2 p1, types::Pos2 p2, types::Pos2 p3, types::RgbaColor color);

			void draw_arc(types::Rect bounding_box, types::RgbaColor color, types::Radius start = 0.0f,
						  types::Radius end = math::pi * 2, float width = 1.0f);

			void draw_pie(types::Rect bounding_box, types::RgbaColor color, types::Radius start = 0.0f,
						  types::Radius end = math::pi * 2);

			void draw_surface(const Surface &surface);

			void clear(types::RgbaColor background = { 0, 0, 0, 0 });

			static error::Result<Surface> create(types::Size2 size);

			static error::Result<Surface> load_file(const std::filesystem::path &path);
	};
}  // namespace ezml::surface
