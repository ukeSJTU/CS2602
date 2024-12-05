# CS2602
本代码仓库对应上海交通大学IEEE专业CS2602课程，主要包含课本代码以及课后习题。课本采用《数据结构C++语言描述》慕课版。上课老师：张同珍老师。





# 项目构建和使用指南

## 环境配置

在开始之前，确保你的系统已安装了以下软件：

- **CMake**：用于构建项目的工具。你可以通过以下命令安装 CMake（以 Ubuntu 为例）：

```bash
sudo apt-get install cmake
```

如果使用的是 macOS，可以通过 Homebrew 安装 CMake：

```bash
brew install cmake
```

- **Google Test**：该项目使用 Google Test 作为单元测试框架，CMake 将自动下载并构建它。

## 第一次配置和构建项目

1. 克隆项目仓库到本地：

```bash
git clone https://github.com/ukeSJTU/CS2602.git
cd CS2602
```

2. 创建构建目录并进入该目录：

```bash
mkdir build
cd build
```

3. 运行 CMake 配置项目：

```bash
cmake ..
```

CMake 会检查你的项目结构，配置编译设置，并生成一个 `Makefile` 文件。

4. 构建项目：

```bash
cmake --build .
```

这将根据 `CMakeLists.txt` 中的配置，自动编译所有源文件和测试文件，并生成可执行文件。

## 编译特定源文件

在 `src/` 文件夹下的所有源文件都会被自动检测到并添加到构建中。如果你希望仅编译某一个特定的文件，可以通过修改 `CMakeLists.txt` 来指定你想要编译的文件。例如：

```cmake
add_executable(Chapter2_3 src/examples/Chapter2/2-3.cpp)
```

然后，你可以使用 `cmake --build .` 命令来编译这个特定的文件。

## 运行测试

1. 在构建完成后，你可以运行所有单元测试：

```bash
ctest
```

或者，你可以运行特定的测试：

```bash
./test/test_seqlist
```

这会执行对应的测试可执行文件。

## 修改头文件/源代码后重新编译

如果你修改了头文件或源代码，或者添加了新的测试文件，只需要执行以下步骤来重新编译项目：

1. 进入构建目录：

```bash
cd build
```

2. 运行 CMake 以检查更改：

```bash
cmake ..
```

3. 然后，运行 `cmake --build .` 来重新编译所有文件：

```bash
cmake --build .
```

这样，CMake 会重新检测所有文件的更改并重新编译项目。

## 清理构建

如果你想清理构建目录，可以删除整个 `build/` 文件夹：

```bash
rm -rf build/
```

然后重新创建该文件夹并运行 `cmake` 重新构建。


# 合并源代码与头文件

如果你像我一样，自己整理了一个头文件目录(`./include`)，你应该会觉得做OJ题目还是挺轻松的，毕竟很多基本代码你已经在脚本代码里面实现了，但是我当时做OJ仍然很痛苦，因为我本地做题可能会在main.cpp中写很多的`#include "SeqList.h"`等等，有时候本地测试了一下发现一切正常，遂急急忙忙提交到了OJ平台上面结果2秒后喜提**COMPILE ERROR**。着实令人恼火，痛定思痛写了一个python脚本来自动化这个流程，使用方法如下：

以下是为 `merge_to_oj.py` 脚本生成的简单 Markdown 使用指南：

# `merge_to_oj.py` 使用指南

## 简介
`merge_to_oj.py` 是一个用于自动合并 C++ 源代码及其依赖的工具，特别适用于在线评测（OJ）平台无法上传多文件的情况。它能够解析 `#include` 指令，找到自定义头文件，并将其内容递归合并到主程序中。

---

## 环境要求
- Python 3.7 或更高版本
- 可选：`clang-format`（用于代码格式化）

---

## 功能特性
- **自动解析**：识别主文件中的 `#include` 并递归合并自定义头文件内容。
- **指定题目编号**：通过题目编号快速指定要合并的文件。
- **批量处理**：支持一次性处理多个文件。
- **代码格式化**：自动检测并使用 `clang-format` 格式化输出代码。
- **覆盖控制**：可选择是否覆盖已有的 `merged.cpp` 文件。

---

## 使用方法

### 1. 查看帮助信息
运行以下命令查看完整的参数说明：
```bash
python merge_to_oj.py --help
```

输出示例：
```
usage: merge_to_oj.py [-h] [-i [IDS ...]] [-f] [--no-format]

自动合并 C++ 源文件及其依赖的头文件

optional arguments:
  -h, --help            显示帮助信息
  -i [IDS ...], --ids [IDS ...]
                        指定题目编号 ID（如 2498 2526），默认处理所有文件
  -f, --force           强制覆盖已存在的 merged.cpp 文件
  --no-format           不格式化输出文件
```

---

### 2. 合并文件

#### 合并所有文件
默认会处理 `./src/homework/***/main.cpp` 中的所有文件，并生成对应的 `merged.cpp` 文件：
```bash
python merge_to_oj.py
```

#### 指定题目编号
如果只想合并特定题目（如编号为 `2498` 和 `2526`），可以使用 `-i` 参数：
```bash
python merge_to_oj.py -i 2498 2526
```

#### 强制覆盖输出文件
若目标 `merged.cpp` 文件已存在但需要重新生成，可以使用 `-f` 参数强制覆盖：
```bash
python merge_to_oj.py -f
```

---

### 3. 控制代码格式化

#### 自动格式化（默认）
脚本会尝试使用 `clang-format` 自动格式化生成的代码，并检测 `.clang-format` 配置文件。

#### 禁用格式化
如果不需要格式化输出文件，可以添加 `--no-format` 参数：
```bash
python merge_to_oj.py --no-format
```

---

### 4. 输出文件
处理完成后，生成的文件将保存在与 `main.cpp` 文件同一目录下，文件名为 `merged.cpp`。

示例：
```
src/homework/2498/main.cpp   -> src/homework/2498/merged.cpp
src/homework/2526/main.cpp   -> src/homework/2526/merged.cpp
```

---

## 示例场景

### 合并指定编号的题目并格式化代码
```bash
python merge_to_oj.py -i 2498 -f
```

### 合并所有文件但不格式化代码
```bash
python merge_to_oj.py --no-format
```

---

## 注意事项
1. **文件路径**：
   - 自定义头文件需存放在 `./include` 文件夹中。
   - 主文件需按照 `./src/homework/编号/main.cpp` 的结构组织。

2. **循环依赖**：
   - 脚本会自动检测循环依赖并避免重复解析。

3. **格式化工具**：
   - 请确保 `clang-format` 已正确安装并可用。
   - 若未检测到格式化工具，脚本将跳过格式化步骤。

---

## 开发与扩展
- 如果有新的需求或改进建议，请直接修改脚本或提交反馈。

