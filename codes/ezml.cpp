#include <cstdint>
#include <filesystem>
#include <optional>
#include <string_view>
#include <variant>

/* Ezml api 草案 v0.1.0
 * 本文件仅为草案
 * 2026-9-25
 * */

namespace ezml {
	namespace types {
		template<typename T>
		struct Vec2 {
			T x, y;
		};

		using Vec2i = Vec2<std::int64_t>;
		using Vec2u = Vec2<std::uint64_t>;
		using Vec2f = Vec2<float>;

		using Pos2 = Vec2f;
		using Size2 = Vec2f;
		using WinSize = Vec2u;

		struct Rect {
			Pos2 pos;
			Size2 size;
		};

	};

	namespace surface {
		class Surface {
			/* 表示一个抽象的绘制目标
			 * */
			public:
				Surface(types::Size2 size);

				void draw_px(types::Pos2 pos);

				void draw_line(types::Pos2 p1, types::Pos2 p2);

				// 其他绘制api...
				// 例如矩形,三角形
				
				friend Surface load_file(const std::filesystem::path &path);
		};

		Surface load_file(const std::filesystem::path &path);
		
	};

	namespace keyboard {
		enum class KeyboardKey {
			A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, // 字母
			N0,N1,N2,N3,N4,N5,N6,N7,N8,N9, // 数字
			F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12, // Fn
			Esc,Tab,Caps,LCtrl,RCtrl,LAlt,RAlt,LShift,RShift,Enter, // 功能键
			// 符号
			ArrowUp,ArrowDown,ArrowLeft,ArrowRight, // 箭头按键
		}; 
		
		bool is_key_pressed(KeyboardKey key);
	}

	namespace event {
		struct KeyboardPressedEvevt {
			keyboard::KeyboardKey key;
			bool shift, ctrl, alt, system;
		};
		
		struct KeyboardReleasedEvevt {
			keyboard::KeyboardKey key;
		};

		struct WindowCloseEvent {};

		struct WindowResizeEvent {
			types::Size2 size;
		};

		enum class MouseKey {
			Left, Wheel, Right
		};

		struct MousePressedEvent {
			types::Pos2 pos;
			MouseKey Key;
		};

		struct MouseReleasedEvent {
			types::Pos2 pos;
			MouseKey key;
		};

		// 其他事件结构体...
		// 例如鼠标滚轮,窗口焦点
		
		using NoEvent =  std::monostate; // 表示事件队列已空

		using Event = std::variant<
			NoEvent,
			WindowCloseEvent,
			WindowResizeEvent,
			KeyboardPressedEvevt,
			KeyboardReleasedEvevt,
			MousePressedEvent,
			MouseReleasedEvent
		>;
	};

	namespace window {
		
		class Icon{
			/* 表示一个窗口图标
			 * */
		};

		class Window {
			/* 表示一个操作系统的窗口
			 * */
			public:
				Window(std::string_view caption, types::WinSize size, const std::optional<Icon> &icon);

				surface::Surface &surface_ref();

				void set_caption(std::string_view caption);

				void set_size(types::WinSize size);

				void set_icon(const std::optional<Icon> &icon);

				std::optional<types::Pos2> mouse_pos();

				event::Event poll_event();
		};
	};
};
