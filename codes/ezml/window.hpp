#pragma once

#include <filesystem>
#include <optional>
#include <string_view>

#include "ezml/error.hpp"
#include "ezml/event.hpp"
#include "ezml/keyboard.hpp"
#include "ezml/mouse.hpp"
#include "ezml/surface.hpp"
#include "ezml/types.hpp"

namespace ezml::window {

	class Icon {
			/* 表示一个图标
			 * */
		protected:
			Icon(const std::filesystem::path &file);

		public:
			Icon(const Icon &icon) = delete;
			Icon operator=(const Icon &icon) = delete;

			Icon(Icon &&icon);
			Icon &operator=(Icon &&icon);

			static error::Result<Icon> load_file(const std::filesystem::path &file);
	};

	class Window {
			/* 表示一个操作系统的窗口
			 * */
		protected:
			Window(std::string_view caption, types::WinSize size, const std::optional<Icon> &icon,
				   types::RgbColor background = { 0, 0, 0 });

		public:
			Window(const Window &window) = delete;
			Window operator=(const Window &window) = delete;

			Window(Window &&window);
			Window &operator=(Window &&window);

			surface::Surface &surface_ref();

			// 窗口数据

			void set_caption(std::string_view caption);

			void set_size(types::WinSize size);

			void set_icon(const std::optional<Icon> &icon);

			void set_background(types::RgbColor background = { 0, 0, 0 });

			// 键鼠

			std::optional<types::Pos2> mouse_pos();

			bool is_key_pressed(keyboard::Key key);

			bool is_mouse_button_pressed(mouse::Key key);

			void show_cursor();

			void hide_cursor();

			void set_cursor(const Icon &icon);

			// 窗口状态

			void show();

			void hide();

			void close();

			void minimize();

			void maximize();

			void restore();

			void fullscreen();

			// 绘制

			// 将surface_ref返回的Surface引用的内容同步到窗口
			void update();

			// 事件

			event::Event poll_event();

			static error::Result<Window> create(std::string_view caption, types::WinSize size,
												const std::optional<Icon> &icon);
	};
}  // namespace ezml::window
