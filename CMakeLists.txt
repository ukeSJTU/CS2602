# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(CS2602)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定头文件目录
include_directories(include)

# 启用测试功能
enable_testing()

# 添加 Google Test 子模块
add_subdirectory(third_party/gtest)

# 查找所有 main.cpp 文件
file(GLOB_RECURSE MAIN_SOURCES "src/**/main.cpp")

# 为每个 main.cpp 创建独立的可执行文件
foreach(MAIN_FILE ${MAIN_SOURCES})
    # 获取相对路径作为可执行文件名
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR}/src ${MAIN_FILE})
    get_filename_component(PARENT_DIR ${REL_PATH} DIRECTORY)
    string(REPLACE "/" "_" EXECUTABLE_NAME "${PARENT_DIR}")
    
    # 为每个 main.cpp 创建一个可执行文件
    add_executable(${EXECUTABLE_NAME} ${MAIN_FILE})
endforeach()

# 设置测试源文件目录
file(GLOB TEST_SOURCES "test/*.cpp")

# 循环为每个测试文件生成独立的可执行文件
foreach(TEST_FILE ${TEST_SOURCES})
    # 获取文件名，不包含路径和扩展名
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # 为每个测试源文件创建一个可执行文件
    add_executable(${TEST_NAME} ${TEST_FILE})
    
    # 链接 Google Test 库
    target_link_libraries(${TEST_NAME} gtest gtest_main)
    
    # 启用测试
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# 配置生成编译数据库
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
