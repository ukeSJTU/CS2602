# CS2602

本代码仓库对应上海交通大学 IEEE 专业 CS2602 课程。本课程课本采用《数据结构 C++语言描述》慕课版。任课教师：张同珍老师。

如果你觉得这个仓库对你有所帮助的话请给我一个 Star 吧。

如果你发现这个仓库还有需要完善的地方，欢迎提出 issue 甚至 PR。

> **注意：** 作者本人也正在学习这门课程，所以本仓库还处于快速开发过程当中，很多内容还不完善，请见谅。

- [CS2602](#cs2602)
- [Features](#features)
  - [更加规范化的开发过程](#更加规范化的开发过程)
  - [高效的自动化脚本](#高效的自动化脚本)
  - [更多参考资料](#更多参考资料)
- [Getting Started](#getting-started)
  - [克隆仓库](#克隆仓库)
  - [环境配置](#环境配置)
    - [1. C++编译器 (g++)](#1-c编译器-g)
    - [2. CMake (3.10+)](#2-cmake-310)
    - [3. 构建工具](#3-构建工具)
    - [4. Python 3.6+ (用于自动化脚本)](#4-python-36-用于自动化脚本)
    - [5. clang-format (可选，用于代码格式化)](#5-clang-format-可选用于代码格式化)
    - [验证环境配置](#验证环境配置)
  - [第一次编译并运行](#第一次编译并运行)
  - [运行测试](#运行测试)
  - [修改头文件/源代码后重新编译](#修改头文件源代码后重新编译)
  - [清理构建](#清理构建)
- [工程目录结构](#工程目录结构)
- [工具](#工具)
  - [合并源代码与头文件 (merge_to_oj.py)](#合并源代码与头文件-merge_to_ojpy)
    - [使用方法](#使用方法)
    - [功能特点](#功能特点)
  - [本地测试工具 (oj_evaluator.py)](#本地测试工具-oj_evaluatorpy)
    - [使用方法](#使用方法-1)
    - [功能特点](#功能特点-1)
    - [测试用例格式](#测试用例格式)
- [Q\&A](#qa)

# Features

## 更加规范化的开发过程

使用了 Cmake 编译， Google Test 自动化测试，clang-format 格式化等等。绝大部分头文件添加 doxygen 注释，IDE 开发提示更智能，等等。

## 高效的自动化脚本

项目中有两个 python 脚本可以帮助你快速测试自己的代码，不需要等待 OJ 可以在本地先测试，也可以合并头文件生成一份独立的源程序方便你提交，不要再因为忘记/缺少自己实现的头文件导致 ACM-OJ 出现 CE 错误。

## 更多参考资料

除了课本内容，本仓库还融合了上课的 PPT，以及《大话数据结构》这本书。

# Getting Started

## 克隆仓库

本项目使用了 Google Test，需要一起下载：

```bash
git clone https://github.com/ukeSJTU/CS2602.git --recursive
```

## 环境配置

本项目需要以下工具来编译和运行代码。以下是详细的安装说明：

### 1. C++编译器 (g++)

这是编译 `C++` 代码的核心工具。

- **Windows**:

  - 推荐使用 MinGW-w64：
    1. 访问 [MinGW-w64 下载页面](https://www.mingw-w64.org/downloads/)
    2. 下载并运行安装程序
    3. 将 MinGW 的 bin 目录添加到系统环境变量 PATH 中
    4. 打开命令提示符，输入 `g++ --version` 验证安装

- **macOS**:

  ```bash
  # 通过Homebrew安装
  brew install gcc

  # 验证安装
  g++ --version
  ```

- **Linux (Ubuntu/Debian)**:

  ```bash
  # 安装编译器
  sudo apt update
  sudo apt install build-essential

  # 验证安装
  g++ --version
  ```

### 2. CMake (3.10+)

CMake 是一个跨平台的构建系统，用于管理项目的编译过程。

- **Windows**:

  1. 访问 [CMake 官方下载页面](https://cmake.org/download/)
  2. 下载并安装 Windows 安装程序
  3. 安装时选择"Add CMake to the system PATH"
  4. 打开新的命令提示符，输入 `cmake --version` 验证安装

- **macOS**:

  ```bash
  # 通过Homebrew安装
  brew install cmake

  # 验证安装
  cmake --version
  ```

- **Linux (Ubuntu/Debian)**:

  ```bash
  sudo apt update
  sudo apt install cmake

  # 验证安装
  cmake --version
  ```

### 3. 构建工具

- **Windows 平台**需要选择以下一种：

  a) **Ninja** (推荐):

  ```bash
  # 通过pip安装
  pip install ninja

  # 验证安装
  ninja --version
  ```

  b) **Visual Studio**:

  - 访问 [Visual Studio 下载页面](https://visualstudio.microsoft.com/downloads/)
  - 下载 Community 版本（免费）
  - 安装时选择"使用 C++的桌面开发"工作负载

### 4. Python 3.6+ (用于自动化脚本)

如果你想使用项目提供的自动化工具，需要 Python 3.6 或更高版本。

- **Windows**:

  1. 访问 [Python 官网](https://www.python.org/downloads/)
  2. 下载并运行安装程序
  3. 安装时勾选"Add Python to PATH"
  4. 打开新的命令提示符，输入 `python --version` 验证安装

- **macOS**:

  ```bash
  # 通过Homebrew安装
  brew install python

  # 验证安装
  python3 --version
  ```

- **Linux (Ubuntu/Debian)**:

  ```bash
  sudo apt update
  sudo apt install python3 python3-pip

  # 验证安装
  python3 --version
  ```

### 5. clang-format (可选，用于代码格式化)

这是一个可选工具，用于保持代码风格一致。

- **Windows**:

  ```bash
  # 通过pip安装
  pip install clang-format

  # 验证安装
  clang-format --version
  ```

- **macOS**:

  ```bash
  brew install clang-format

  # 验证安装
  clang-format --version
  ```

- **Linux (Ubuntu/Debian)**:

  ```bash
  sudo apt install clang-format

  # 验证安装
  clang-format --version
  ```

### 验证环境配置

完成上述工具安装后，可以运行以下命令验证环境是否配置正确：

```bash
# 验证C++编译器
g++ --version

# 验证CMake
cmake --version

# 验证Python（如果需要使用自动化脚本）
python --version  # Windows
python3 --version  # macOS/Linux

# 验证clang-format（如果已安装）
clang-format --version
```

如果以上命令都能正常显示版本信息，说明环境配置已经完成。

## 第一次编译并运行

1. 创建构建目录并进入该目录：

```bash
mkdir build
cd build
```

2. 运行 CMake 配置项目：

在 Windows 平台上：

```bash
cmake -G "Ninja" ..
```

在 macOS/Linux 电脑上：

```bash
cmake ..
```

3. 构建项目：

```bash
cmake --build .
```

所有生成的文件都在 build/bin/ 文件夹下。运行示例：

macOS/Linux:

```bash
./bin/homework_2498
```

Windows:

```cmd
.\bin\homework_2498.exe
```

## 运行测试

1. 运行所有单元测试：

```bash
ctest
```

2. 运行特定测试：

```bash
./bin/test_seqlist  # macOS/Linux
.\bin\test_seqlist.exe  # Windows
```

## 修改头文件/源代码后重新编译

1. 进入构建目录：

```bash
cd build
```

2. 运行 CMake 检查更改：

```bash
cmake ..
```

3. 重新编译：

```bash
cmake --build .
```

## 清理构建

删除整个 build/ 文件夹：

```bash
rm -rf build/  # macOS/Linux
rmdir /s /q build  # Windows
```

# 工程目录结构

为了让你更方便的使用这个仓库，或者你想要自己修改甚至改进本仓库，以下是各文件夹与文件的作用：

- `docs/`: 按章节编号组织的笔记和 OJ 习题解答

  - 每个章节的 markdown 文件包含笔记和习题解答
  - 部分内容参考了《大话数据结构》

- `include/`: 实现的数据结构

  - 基本实现与课本相同
  - 添加了 namespace datastructures
  - 添加了 doxygen 注释
  - 树相关代码抽象了结点基类，可能与书本略有不同
  - 如果只想用书本实现，可在 docs 对应小节找到代码

- `src/`: 源程序目录

  - `examples/`: 书本示例代码，按章节编号组织
  - `homework/`: ACM-OJ 课后作业，按题目编号组织
  - `homework/index.md`: 记录作业习题编号和完成情况

- `test/`: 单元测试程序

  - 用于测试 include/下实现的数据结构

- `testcases/`: 自定义测试数据

  - 用于本地测试课后作业

- `CMakeLists.txt`: CMake 配置文件

  - 如果你不理解请不要修改
  - 包含 Emscripten 配置(用于网页展示，开发中)

- `.clang-format`: 代码格式化配置文件

# 工具

## 合并源代码与头文件 (merge_to_oj.py)

这个工具可以自动合并你的 main.cpp 文件和它依赖的所有头文件，生成一个独立的源文件用于提交到 OJ 平台。

### 使用方法

1. 基本用法 - 处理所有作业：

```bash
python merge_to_oj.py
```

2. 处理特定题目：

```bash
python merge_to_oj.py -i 2498 2526
```

3. 强制覆盖已存在的 merged.cpp：

```bash
python merge_to_oj.py -f
```

4. 不进行代码格式化：

```bash
python merge_to_oj.py --no-format
```

5. 清理生成的文件：

```bash
python merge_to_oj.py --clean
```

### 功能特点

- 自动递归解析和合并所有依赖的头文件
- 保留系统头文件的 include 语句
- 自动使用 clang-format 格式化生成的代码
- 添加生成时间戳和原始文件标记
- 支持强制覆盖和清理功能

## 本地测试工具 (oj_evaluator.py)

这个工具可以在本地运行和测试你的程序，无需等待 OJ 平台的结果。

### 使用方法

1. 测试所有有测试用例的题目：

```bash
python oj_evaluator.py
```

2. 测试特定题目：

```bash
python oj_evaluator.py -i 14151 14152
```

3. 指定测试用例目录：

```bash
python oj_evaluator.py --testcases_dir ./my_testcases
```

4. 指定可执行文件目录：

```bash
python oj_evaluator.py --binary_dir ./my_build/bin
```

### 功能特点

- 自动查找和运行测试用例
- 彩色输出测试结果
- 显示详细的对比信息
- 支持超时检测
- 汇总测试结果统计

### 测试用例格式

在 `testcases/homework/题号/` 目录下创建测试用例文件：

- `1-in.txt`: 输入数据
- `1-out.txt`: 期望输出
- `2-in.txt`: 第二组输入数据
- `2-out.txt`: 第二组期望输出
  ...以此类推

# Q&A

1. **为什么要使用 CMake 而不是直接编译？**

   - CMake 提供了跨平台的构建系统
   - 更容易管理依赖关系
   - 支持自动化测试
   - 方便配置编译选项

2. **如何添加新的测试用例？**

   - 在 testcases/homework/对应题号下创建输入输出文件对
   - 输入文件命名为 x-in.txt
   - 输出文件命名为 x-out.txt
   - x 为测试用例编号，从 1 开始

3. **如何贡献代码？**

   - Fork 本仓库
   - 创建新的分支
   - 提交改动
   - 发起 Pull Request

4. **遇到编译错误怎么办？**

   - 检查是否正确安装了所有依赖
   - 确保 CMake 版本满足要求
   - 查看 build 目录下的 CMake 错误日志
   - 提 issue 寻求帮助

5. **为什么`include/`中实现的稍微有些不同？**
   - 最主要的不同就在于返回元素值还是返回元素引用，书本上的示例代码基本都返回了元素值，但是我在自己的课后作业中也大量使用了我自己实现的头文件，这个时候如果返回元素值会导致你没有办法从外部修改容器中的元素。具体可以看 `homework-2449` 中使用 `SeqQueue` 的部分。
