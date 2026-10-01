#include <cstdint>
#include <expected>
#include <filesystem>
#include <numbers>
#include <optional>
#include <string_view>
#include <variant>

/* Ezml api 草案 v0.1.3
 * 本文件仅为草案
 * 创建时间: 2026-9-25
 * 修改时间: 2026-10-2
 * */

namespace ezml {
	enum class Error {	// 错误码定义
		FileNotFound,
		//...
	};

	template <typename T>
	using Result = std::expected<T, Error>;

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

	}  // namespace types

	types::Radius pi = std::numbers::pi_v<types::Radius>;

	namespace surface {
		class Surface {
				/* 表示一个抽象的绘制目标
				 * */
			protected:
				Surface(types::Size2 size);

			public:
				Surface(const Surface &w) = delete;
				Surface operator=(const Surface &w) = delete;

				Surface(Surface &&w);
				Surface operator=(Surface &&w);

				void draw_px(types::Pos2 pos, types::RgbaColor color);

				void draw_line(types::Pos2 p1, types::Pos2 p2, types::RgbaColor color, float width = 1.0f);

				void draw_rect(types::Rect, types::RgbaColor color);

				void draw_trangle(types::Pos2 p1, types::Pos2 p2, types::Pos2 p3, types::RgbaColor color);

				void draw_arc(types::Rect bauding_box, types::RgbaColor color, types::Radius start = 0.0f,
							  types::Radius end = pi * 2, float width = 1.0f);

				void draw_pie(types::Rect bauding_box, types::RgbaColor color, types::Radius start = 0.0f,
							  types::Radius end = pi * 2);

				// 其他绘制api...
				// 例如矩形,三角形

				static Result<Surface> create(types::Size2 size);

				friend Result<Surface> load_file(const std::filesystem::path &path);
		};

		Result<Surface> load_file(const std::filesystem::path &path);

	}  // namespace surface

	namespace keyboard {
		enum class Key {
			// 字母
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			// 数字
			N0,
			N1,
			N2,
			N3,
			N4,
			N5,
			N6,
			N7,
			N8,
			N9,
			// Fn
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			// 主键盘功能键
			Esc,
			Tab,
			Caps,
			LeftCtrl,
			RightCtrl,
			LeftAlt,
			RightAlt,
			LeftShift,
			RightShift,
			Enter,
			// 符号
			SubtractOrUnderline,
			AddOrEqual,
			SemicolonOrColon,
			CommaOrLessThan,
			PeriodOrGreatThan,
			SlashOrSeparator,
			BackSlashOrQuestion,
			LeftBraceOrSquare,
			RightBraceOrSquareQuote,
			BackQuoteOrTilde,
			// 其他功能键
			SystemRequest,
			ScreenLock,
			Pause,
			Insert,
			Delete,
			Home,
			End,
			PageUp,
			PageDown,
			// 箭头按键
			ArrowUp,
			ArrowDown,
			ArrowLeft,
			ArrowRight,
		};	// 暂不考虑小键盘

		bool is_key_pressed(Key key);
	}  // namespace keyboard

	namespace mouse {
		enum class Key { Left, Wheel, Right };

		enum class WheelDirection { Vertical, Horizontal };
	}  // namespace mouse

	namespace event {
		using NoEvent = std::monostate;	 // 表示事件队列已空

		struct WindowCloseEvent {};

		struct WindowResizeEvent {
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
			std::variant<NoEvent, WindowCloseEvent, WindowResizeEvent, WindowFocusLostEvent, WindowFocusGainedEvent,
						 KeyboardPressEvent, KeyboardReleaseEvent, KeyboardTextEnteredEvent, MousePressEvent,
						 MouseReleaseEvent, MouseWheelScrolled, MouseMoveEvent>;
	}  // namespace event

	namespace window {

		class Icon {
			public:
				enum class ScaleLevel {
					/* 缩放尺寸
					 * */
				};
				/* 表示一个窗口图标
				 * */

				Result<void> load_file(const std::filesystem::path &file, ScaleLevel level);
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

				void set_caption(std::string_view caption);

				void set_size(types::WinSize size);

				void set_icon(const std::optional<Icon> &icon);

				std::optional<types::Pos2> mouse_pos();

				event::Event poll_event();

				static Result<Window> create(std::string_view caption, types::WinSize size,
											 const std::optional<Icon> &icon);
		};
	}  // namespace window
}  // namespace ezml
