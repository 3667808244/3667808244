#pragma once

#include <variant>

#include "ezml/keyboard.hpp"
#include "ezml/mouse.hpp"
#include "ezml/types.hpp"

namespace ezml::event {
	using NoEvent = std::monostate;	 // 表示事件队列已空

	// 窗口事件
	struct WindowCloseRequestEvent {};

	struct WindowResizeRequestEvent {
			types::WinSize size;
	};

	struct WindowFocusLostEvent {};

	struct WindowFocusGainedEvent {};

	// 键盘事件
	struct KeyboardPressEvent {
			keyboard::Key key;
			bool shift, ctrl, alt, system;
	};

	struct KeyboardReleaseEvent {
			keyboard::Key key;
			bool shift, ctrl, alt, system;
	};

	struct KeyboardTextEnteredEvent {
			char32_t code;
	};

	// 鼠标事件
	struct MousePressEvent {
			types::Pos2 pos;
			mouse::Key key;
	};

	struct MouseReleaseEvent {
			types::Pos2 pos;
			mouse::Key key;
	};

	struct MouseEnterEvent {};

	struct MouseLeftEvent {};

	struct MouseWheelScrolled {
			types::Pos2 pos;
			float delta;
			mouse::WheelDirection direction;  // 在Windows下按shift再滚轮可能会变成横向
	};

	struct MouseMoveEvent {
			types::Pos2 pos;
	};

	// clang-format off
	using Event = std::variant<
		NoEvent, 
		// 窗口事件
		WindowCloseRequestEvent, 
		WindowResizeRequestEvent, 
		WindowFocusLostEvent,
		WindowFocusGainedEvent, 
		// 键盘事件
		KeyboardPressEvent, 
		KeyboardReleaseEvent, 
		KeyboardTextEnteredEvent,
		// 鼠标事件
		MousePressEvent,
		MouseReleaseEvent,
		MouseEnterEvent,
		MouseLeftEvent,
		MouseWheelScrolled,
		MouseMoveEvent
	>;
	// clang-format on
}  // namespace ezml::event
