import os
import re
import argparse
import platform
import subprocess
import shutil


INCLUDE_DIR = './include'
HOMEWORK_DIR = './src/homework'


def parse_includes(file_path, processed_files=None):
    """
    递归解析用户头文件并合并
    """
    if processed_files is None:
        processed_files = set()

    if file_path in processed_files:
        return ""  # 避免重复解析文件

    processed_files.add(file_path)

    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    merged_code = []
    include_pattern = re.compile(r'#include\s+["<](.*?)[">]')

    for line in lines:
        match = include_pattern.match(line)
        if match:
            header = match.group(1)
            if header.endswith('.h'):  # 判断是头文件
                user_header_path = os.path.join(INCLUDE_DIR, header)
                if os.path.exists(user_header_path):
                    # 用户头文件：递归解析
                    merged_code.append(parse_includes(user_header_path, processed_files))
                else:
                    # 系统头文件：直接保留
                    merged_code.append(line)
            else:
                merged_code.append(line)
        else:
            merged_code.append(line)

    return ''.join(merged_code)


def merge_cpp(main_file_path, output_file_path, force=False):
    """
    合并主文件及其依赖的头文件
    """
    if not os.path.exists(main_file_path):
        print(f"主文件 {main_file_path} 不存在！")
        return

    if os.path.exists(output_file_path) and not force:
        print(f"输出文件 {output_file_path} 已存在，使用 -f/--force 参数强制覆盖")
        return

    merged_code = parse_includes(main_file_path)

    with open(output_file_path, 'w', encoding='utf-8') as output_file:
        output_file.write(merged_code)

    print(f"合并完成！输出文件：{output_file_path}")


def format_code(file_path):
    """
    格式化代码
    """
    system = platform.system().lower()
    clang_format = "clang-format"

    # 检测平台与格式化工具
    if system == "windows":
        clang_format = "clang-format.exe"
    elif system == "linux" or system == "darwin":
        clang_format = "clang-format"

    # 检测是否有格式化工具
    if not shutil.which(clang_format):
        print("未检测到 clang-format 工具，跳过格式化")
        return

    # 检测 .clang-format 配置文件
    if os.path.exists(".clang-format"):
        print("检测到 .clang-format 配置文件，将使用该配置格式化代码")

    # 执行格式化
    try:
        subprocess.run([clang_format, "-i", file_path], check=True)
        print(f"格式化完成：{file_path}")
    except subprocess.CalledProcessError as e:
        print(f"格式化失败：{file_path}，错误信息：{e}")


def get_main_files(ids=None):
    """
    获取所有需要处理的 main.cpp 文件路径
    """
    if ids:
        return [
            os.path.join(HOMEWORK_DIR, f"{id_}/main.cpp")
            for id_ in ids
            if os.path.exists(os.path.join(HOMEWORK_DIR, f"{id_}/main.cpp"))
        ]
    else:
        # 默认查找所有 homework 下的 main.cpp 文件
        main_files = []
        for root, _, files in os.walk(HOMEWORK_DIR):
            for file in files:
                if file == "main.cpp":
                    main_files.append(os.path.join(root, file))
        return main_files


def main():
    parser = argparse.ArgumentParser(description="自动合并 C++ 源文件及其依赖的头文件")
    parser.add_argument(
        "-i",
        "--ids",
        nargs="*",
        type=str,
        help="指定题目编号 ID（如 2498 2526），默认处理所有文件",
    )
    parser.add_argument(
        "-f", "--force", action="store_true", help="强制覆盖已存在的 merged.cpp 文件"
    )
    parser.add_argument(
        "--no-format", action="store_true", help="不格式化输出文件"
    )
    args = parser.parse_args()

    # 获取 main.cpp 文件列表
    main_files = get_main_files(args.ids)

    if not main_files:
        print("未找到任何需要处理的 main.cpp 文件")
        return

    # 处理每个文件
    for main_file in main_files:
        output_file = os.path.join(os.path.dirname(main_file), "merged.cpp")
        merge_cpp(main_file, output_file, force=args.force)

        if not args.no_format:
            format_code(output_file)


if __name__ == "__main__":
    main()