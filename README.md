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
