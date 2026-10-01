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
