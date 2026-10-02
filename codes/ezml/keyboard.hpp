#pragma once

namespace ezml {
	// clang-format off
	namespace keyboard {
		enum class Key {
			// 字母
			A, B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			// 数字
			N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
			// Fn
			F1, F2, F3, F4, F5, F6,
			F7, F8, F9, F10, F11, F12,
			// 主键盘功能键
			Esc, Tab, Caps, Enter,
			LeftCtrl, RightCtrl,
			LeftAlt, RightAlt,
			LeftShift, RightShift,
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
			Insert, Delete,
			Home, End,
			PageUp, PageDown,
			// 箭头按键
			ArrowUp,
			ArrowDown,
			ArrowLeft,
			ArrowRight,
		};	// 暂不考虑小键盘
		// clang-format on
	}  // namespace keyboard
}  // namespace ezml
