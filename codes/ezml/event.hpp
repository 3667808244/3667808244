#pragma once

#include <variant>

#include "ezml/keyboard.hpp"
#include "ezml/mouse.hpp"
#include "ezml/types.hpp"

namespace ezml {
	namespace event {
		using NoEvent = std::monostate;	 // 表示事件队列已空

		struct WindowCloseRequestEvent {};

		struct WindowResizeRequestEvent {
				types::WinSize size;
		};

		struct WindowFocusLostEvent {};

		struct WindowFocusGainedEvent {};

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

		struct MousePressEvent {
				types::Pos2 pos;
				mouse::Key key;
		};

		struct MouseReleaseEvent {
				types::Pos2 pos;
				mouse::Key key;
		};

		struct MouseWheelScrolled {
				types::Pos2 pos;
				float delta;
				mouse::WheelDirection direction;
		};

		struct MouseMoveEvent {
				types::Pos2 pos;
		};

		using Event =
			std::variant<NoEvent, WindowCloseRequestEvent, WindowResizeRequestEvent, WindowFocusLostEvent,
						 WindowFocusGainedEvent, KeyboardPressEvent, KeyboardReleaseEvent, KeyboardTextEnteredEvent,
						 MousePressEvent, MouseReleaseEvent, MouseWheelScrolled, MouseMoveEvent>;
	}  // namespace event
}  // namespace ezml
