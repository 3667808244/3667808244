#pragma once

#include <filesystem>
#include <optional>
#include <string_view>

#include "ezml/event.hpp"
#include "ezml/keyboard.hpp"
#include "ezml/mouse.hpp"
#include "ezml/surface.hpp"
#include "ezml/types.hpp"

namespace ezml {
	namespace window {

		class Icon {
				/* 表示一个图标
				 * */
			protected:
				Icon(const std::filesystem::path &file);

			public:
				Icon(const Icon &w) = delete;
				Icon operator=(const Icon &w) = delete;

				Icon(Icon &&w);
				Icon operator=(Icon &&w);

				static types::Result<void> load_file(const std::filesystem::path &file);
		};

		class Window {
				/* 表示一个操作系统的窗口
				 * */
			protected:
				Window(std::string_view caption, types::WinSize size, const std::optional<Icon> &icon);

			public:
				Window(const Window &w) = delete;
				Window operator=(const Window &w) = delete;

				Window(Window &&w);
				Window operator=(Window &&w);

				surface::Surface &surface_ref();

				// 窗口数据

				void set_caption(std::string_view caption);

				void set_size(types::WinSize size);

				void set_icon(const std::optional<Icon> &icon);

				// 键鼠

				std::optional<types::Pos2> mouse_pos();

				bool is_key_pressed(keyboard::Key key);

				bool is_key_pressed(mouse::Key key);

				void show_cursor();

				void hide_cursor();

				void set_cursor(Icon &icon);

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

				static types::Result<Window> create(std::string_view caption, types::WinSize size,
													const std::optional<Icon> &icon);
		};
	}  // namespace window
}  // namespace ezml
