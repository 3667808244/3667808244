#include <cstdint>
#include <string>
#include <string_view>
#include <variant>

/* Ezml api 草案 v0.1.0
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
		using Vec2f = Vec2<long double>;

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
		};
	};

	namespace event {
		enum class KeyboardKey {
			A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, // 字母
			N0,N1,N2,N3,N4,N5,N6,N7,N8,N9, // 数字
			F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12, // Fn
			Esc,Tab,Cpas,Ctrl,Alt,Enter, // 功能键
			// 符号
			ArrorUp,ArrorDown,ArrorLeft,ArrorRight, // 箭头按键
		}; // 不包含小键盘

		struct KeyboardPressedEvevt {
			KeyboardKey key;
		};
		
		struct KeyboardReleasedEvevt {
			KeyboardKey key;
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
			MouseKey Key;
		};

		// 其他事件结构体...

		using Event = std::variant<
			std::monostate, // 表示事件队列已空
			WindowCloseEvent,
			KeyboardPressedEvevt,
			KeyboardReleasedEvevt,
			MousePressedEvent,
			MouseReleasedEvent
		>;
	};

	namespace window {
		class Window {
			/* 表示一个操作系统的窗口
			 * */
			public:
				Window(std::string_view caption, types::WinSize size);

				surface::Surface &surface_ref();

				void set_caption(std::string_view caption);

				void set_size(types::WinSize size);

				event::Event poll_event();
		};
	};
};
