# FF14ModsDataBase Wiki

```
        *                           *         *
                       *                .

*
          |\___/|
          )     (             .              '
         =\     /=
           )===(       *
          /     \
          |     |
         /       \
         \       /
  _/\_/\_/\__  _/_/\_/\_/\_/\_/\_/\_/\_/\_/\_
  |  |  |  |( (  |  |  |  |  |  |  |  |  |  |
  |  |  |  | ) ) |  |  |  |  |  |  |  |  |  |
  |  |  |  |(_(  |  |  |  |  |  |  |  |  |  |     asciiart.cc
  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
```

# 磨坊Mod数据库项目预览
[拉磨项目预览](https://github.com/oblivion777/FF14ModsDataBase/wiki)

**本项目采用 MIT 开源许可证（MIT License）授权发布。该协议允许用户在保留原始版权和许可声明的前提下，复制、修改、合并、发布、分发本软件及其副本，亦可将其用于商业用途，且无须公开源代码。**

**This project is licensed under the MIT License. You are free to use, modify, and distribute it with proper attribution.**

# 项目所用语言标准与平台说明
本项目采用现代化开发工具与语言标准，以提升代码的可维护性、性能表现与跨平台适配能力。


## 1. 开发与构建环境
集成开发环境：Microsoft Visual Studio 2022

构建系统：MSBuild

Visual Studio 2022 提供对 C++17、C17 以及 .NET 6.0 的完整支持，具备强大的 IntelliSense、诊断工具与多平台编译能力，是现代 C++ 和 .NET 开发的首选环境。

## 2. 编程语言标准

### C++
ISO C++17（编译选项：/std:c++17）

项目 C++ 模块采用 ISO C++17 标准，充分利用如下语言与标准库特性：

结构化绑定（auto [a, b] = ...;）

if constexpr 编译期条件判断

std::optional、std::variant 等现代类型支持

std::string_view 提高字符串处理效率

并发支持增强（如 std::shared_mutex）

### C
ISO C17（2018）（编译选项：/std:c17）

C 模块遵循 ISO C17 标准：

提升跨平台一致性

修复 C11 中若干语言与实现差异问题

更好地与现代 C++ 模块协同工作

## 3. 运行时平台
.NET：.NET 6.0（长期支持版 / LTS）
.NET 6.0 用于构建 Web 服务、工具链组件或托管库模块，具备以下优势：

跨平台支持（Windows / Linux / macOS）

支持最新 C# 10 语法与特性

性能显著提升（包括 GC、JIT、Startup 优化）

长期支持（LTS）保障项目生命周期

![_(:з」∠)_](https://blog.voids.cc/[BBC2C8AC]/%E5%8F%8C%E7%8C%AB%E7%8C%AB.jpg)



