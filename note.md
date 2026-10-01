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

其他内容查看[codes/.clang-format](codes/.clang-format)
没有特别声明时的补全参考(Windows+MSYS2)[codes/.clangd](codes/.clangd)

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
