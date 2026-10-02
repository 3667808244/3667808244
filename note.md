发现一些事情,
我好像总是会把编程的想法带入到游戏中,然后因为太复杂然后放弃

你问我为什么
[机械动力](https://github.com/Creators-of-Create/Create)

你不觉得中央仓库+物流和总线很像吗?

2026-10-3 06:23:10

---

为什么感觉VSCode的c/cpp插件LLVM的clangd插件没有Microsoft的C/C++插件用的多
微软写的有那么好吗,好像每个平台还要重新配编译器和目录

2026-10-3

---

放弃LiveCD了,构建时的过程文件太大了，每次都虚拟机都炸
Docker这类东西又不能裸机启动

还有`EzMediaLibrary`会长期处于草案的状态(至少等我中考完吧)

2026-10-3

---

#  EzMediaLibrary api 预计的使用示例

```cpp
// demo.cpp —— ezml 最小用法示例（结构已通过 g++ -std=c++23 -Wall -Wextra -fsyntax-only）
#include "ezml/ezml.hpp"

#include <cstdint>
#include <expected>
#include <filesystem>
#include <optional>
#include <print>
#include <type_traits>
#include <variant>

int main() {
	using ezml::event::KeyboardPressEvent;
	using ezml::event::MousePressEvent;
	using ezml::event::NoEvent;
	using ezml::event::WindowCloseRequestEvent;
	using ezml::event::WindowResizeRequestEvent;
	using ezml::surface::Surface;
	using ezml::types::RgbaColor;
	using ezml::types::WinSize;
	using ezml::window::Window;

	// ---- 1. 创建窗口: 返回 std::expected<std::unique_ptr<Window>, types::Error>
	auto win = Window::create("ezml demo", WinSize{800, 600}, std::nullopt);
	if (!win) {
		std::println("create window failed, error = {}", static_cast<int>(win.error()));
		return 1;
	}
	Window &window = **win;  // expected -> unique_ptr<Window> -> Window&

	// ---- 2. 拿到窗口自带的绘制目标, 画点东西再同步上去
	Surface &canvas = window.surface_ref();
	const RgbaColor white{255, 255, 255, 255};
	const RgbaColor red{220, 60, 60, 255};

	canvas.draw_rect({{40.0f, 40.0f}, {240.0f, 160.0f}}, red);
	canvas.draw_line({0.0f, 0.0f}, {800.0f, 600.0f}, white, 2.0f);
	canvas.draw_arc({{520.0f, 380.0f}, {200.0f, 200.0f}}, white, 0.0f, ezml::pi / 2);
	window.update();

	window.set_caption("ezml demo");
	window.show();

	// ---- 3. 事件循环: poll_event() 返回 std::variant, 队列空时是 NoEvent
	bool running = true;
	while (running) {
		std::visit(
			[&](auto &&ev) {
				using E = std::decay_t<decltype(ev)>;

				if constexpr (std::is_same_v<E, NoEvent>) {
					// 队列已空, 真实实现里在这里等下一帧
				}
				else if constexpr (std::is_same_v<E, WindowCloseRequestEvent>) {
					running = false;
				}
				else if constexpr (std::is_same_v<E, WindowResizeRequestEvent>) {
					std::println("resize -> {} x {}", ev.size.x, ev.size.y);
				}
				else if constexpr (std::is_same_v<E, KeyboardPressEvent>) {
					if (ev.key == ezml::keyboard::Key::Esc) { running = false; }
				}
				else if constexpr (std::is_same_v<E, MousePressEvent>) {
					if (ev.key == ezml::mouse::Key::Left) { canvas.draw_px(ev.pos, red); }
					window.update();
				}
				else {
					// MouseRelease / MouseMove / MouseWheelScrolled / 焦点事件...
				}
			},
			window.poll_event());
	}

	window.close();

	// ---- 4. 字体: load_file 收的是非 const 左值引用, 得先有具名 path 变量
	std::filesystem::path font_path{"assets/ui.ttf"};
	auto font = ezml::font::Font::load_file(font_path);
	if (!font) {
		std::println("load font failed, error = {}", static_cast<int>(font.error()));
	}
	return 0;
}
```

2026-10-2

---

为什么TRPL的中文译本天天连不上啊

2026-10-2

---

# 关于我的代码风格

目前除了EazyMake基本遵循以下模式:
(可能不规范,有很多是我写py的习惯带到cpp的)

| 符号类型                     | 格式                                                |
| ---------------------------- | --------------------------------------------------- |
| 类型                         |                                                     |
| 类/结构体/枚举等自定义类型名 | PascalCase                                          |
| 类型别名                     | PascalCase 或 snake_case + `_t`后缀                 |
| 变量                         |                                                     |
| 全局变量                     | snake_case                                          |
| 全局常量                     | ALL_CAPS                                            |
| 局部变量                     | snake_case                                          |
| 类成员                       |                                                     |
| 公开成员                     | snake_case                                          |
| 私有/保护成员                | snake_case+`_`前缀                                  |
| 其他                         |                                                     |
| 一般宏                       | ALL_CAPS + `EGGLZH_{project_name}_` 前缀            |
| 保卫宏                       | `EGGLZH_{project_name}_{file_path}_` + `H_`或`HPP_` |

其他内容查看[codes/.clang-format](codes/.clang-format),
ai的概括:
```md
- **缩进与行宽**
  - `UseTab: Always`，使用 Tab 缩进；`TabWidth: 4`、`IndentWidth: 4`
  - `ColumnLimit: 120`
  - 续行缩进 `ContinuationIndentWidth: 4`
  - 访问修饰符缩进：`IndentAccessModifiers: true`
  - 命名空间内容全部缩进：`NamespaceIndentation: All`

- **大括号与换行**
  - `BreakBeforeBraces: Custom`，但 `BraceWrapping` 中类、函数、控制语句、命名空间等基本都**不换行**
  - `AfterControlStatement: Never`
  - 构造函数初始化列表：冒号前换行 `BreakConstructorInitializers: BeforeColon`
  - 继承列表：冒号前换行 `BreakInheritanceList: BeforeColon`

- **对齐**
  - 开括号后对齐：`AlignAfterOpenBracket: Align`
  - 操作数对齐：`AlignOperands: Align`
  - 尾随注释始终对齐，注释前至少 2 个空格
  - 连续赋值、声明、宏等对齐基本关闭

- **短语句/短函数**
  - 短函数、短 lambda 允许单行：`AllowShortFunctionsOnASingleLine: All`
  - 短 `if` 无 `else` 时可单行：`WithoutElse`
  - 短循环可单行：`true`
  - 短块不可单行：`Never`
  - 短枚举可单行，短命名空间不可单行

- **参数与实参**
  - `BinPackArguments: true`
  - `BinPackParameters: BinPack`
  - 允许所有参数/实参放到下一行
  - 整体倾向于压缩排列，而不是每行一个

- **指针、引用与空格**
  - 指针右对齐：`PointerAlignment: Right`
  - 引用按指针风格：`ReferenceAlignment: Pointer`
  - 控制语句前有空格，函数名后无空格
  - 赋值运算符周围有空格
  - C 风格转换后无空格
  - 空花括号内无空格
  - 容器字面量内有空格：`SpacesInContainerLiterals: true`

- **include 排序**
  - 开启排序：`SortIncludes: true`
  - `IncludeBlocks: Regroup`
  - 按 `<ext/*.h>`、`<*.h>`、`<*>`、其他分组排序
  - 支持主头文件识别，如 `test` / `unittest`

- **注释与其他**
  - 注释重排：`ReflowComments: Always`
  - 自动修正命名空间注释：`FixNamespaceComments: true`
  - `using` 声明按字典序数字排序
  - 行尾 LF，文件末尾不自动插入换行
  - 最多保留 1 个空行
  - 整数分隔符不插入
  - C++11 花括号列表使用 Block 风格
  - 包含 Qt、Boost、KJ、absl 等宏和属性支持
```
没有特别声明时的补全参考(Windows+MSYS2)[codes/.clangd](codes/.clangd)
基本就是`isocpp23`

2026-10-2

---

#  EzMediaLibrary api 草案

[codes/ezml.cpp](codes/ezml.cpp)

2026-9-27

---

# 未来可能的方向

目前除了EazyMake还有有这些方向

1. 一个以Deepseek Harness为核心的LiveCD,大概是基于ArchLinux
2. 一个基于SDL3的简单媒体库

2026-9-25

---

你说有没有可能我只是一个初三学生呢?

2026-9-19

---

也是再学校电脑上装上Deepseek Harness了,
不过我为什么要用我自己的api key

2026-9-15

---
