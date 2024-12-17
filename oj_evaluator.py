import os
import subprocess
import argparse
import sys
from pathlib import Path
from collections import defaultdict

# ANSI 转义颜色
RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"


def print_color(text, color):
    print(f"{color}{text}{RESET}")


def parse_args():
    parser = argparse.ArgumentParser(description="自动评测 C++ OJ 类型题目")
    parser.add_argument(
        "-i",
        "--ids",
        nargs="*",
        type=str,
        help="指定题目编号 ID（如 14151 14152），默认处理所有存在的测试用例",
    )
    parser.add_argument(
        "--testcases_dir",
        default="./testcases/homework",
        help="测试用例主目录，默认 ./testcases/homework",
    )
    parser.add_argument(
        "--binary_dir", default="./build/bin", help="可执行文件目录，默认 ./build/bin"
    )
    return parser.parse_args()


def find_binary(problem_id, binary_dir):
    """找到二进制文件"""
    binary_name = f"homework_{problem_id}"
    binary_path = Path(binary_dir) / binary_name
    if os.name == "nt":  # Windows 平台添加 .exe 后缀
        binary_path = binary_path.with_suffix(".exe")
    return binary_path


def get_testcases(testcases_dir, problem_id):
    """获取测试用例的输入输出文件"""
    problem_dir = Path(testcases_dir) / problem_id
    if not problem_dir.exists():
        return []

    testcases = []
    for file in problem_dir.glob("*-in.txt"):
        input_file = file
        output_file = file.with_name(file.name.replace("-in.txt", "-out.txt"))
        if output_file.exists():
            testcases.append((input_file, output_file))
    return testcases


def compile_and_run(binary_path, input_file):
    """运行二进制程序并获取输出"""
    try:
        with open(input_file, "r") as infile:
            result = subprocess.run(
                [str(binary_path)],
                stdin=infile,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=5,  # 设置超时时间，避免死循环
            )
        return result.stdout.strip(), result.stderr.strip()
    except subprocess.TimeoutExpired:
        return None, "Timeout"


def evaluate_testcases(problem_id, binary_path, testcases):
    """评测所有测试用例"""
    summary = {"AC": 0, "WA": 0}
    print_color(f"\n🚀 开始评测题目 {problem_id}...", GREEN)

    for i, (input_file, output_file) in enumerate(testcases, 1):
        print_color(f"🧪 测试用例 {i}: {input_file.name}", BLUE)
        user_output, error_output = compile_and_run(binary_path, input_file)

        if error_output:
            print_color(f"❌ 程序运行错误：{error_output}", RED)
            summary["WA"] += 1
            continue

        with open(output_file, "r") as f:
            expected_output = f.read().strip()

        if user_output == expected_output:
            print_color(f"✅ 测试用例 {i} 通过", GREEN)
            summary["AC"] += 1
        else:
            print_color(f"❌ 测试用例 {i} 未通过", RED)
            print(f"{YELLOW}期望输出：{RESET}\n{expected_output}")
            print(f"{YELLOW}实际输出：{RESET}\n{user_output}")
            summary["WA"] += 1

    total = summary["AC"] + summary["WA"]
    print_color(
        f"\n🎯 题目 {problem_id} 测试结果：{summary['AC']}/{total} AC, {summary['WA']}/{total} WA",
        GREEN if summary["WA"] == 0 else RED,
    )
    return summary


def main():
    args = parse_args()
    testcases_dir = Path(args.testcases_dir)
    binary_dir = Path(args.binary_dir)

    # 获取所有题目编号或指定编号
    problem_ids = (
        args.ids
        if args.ids
        else [p.name for p in testcases_dir.iterdir() if p.is_dir()]
    )
    if not problem_ids:
        print_color("⚠️ 未找到任何测试用例目录，请检查路径。", YELLOW)
        sys.exit(1)

    total_summary = defaultdict(int)

    for problem_id in problem_ids:
        binary_path = find_binary(problem_id, binary_dir)
        testcases = get_testcases(testcases_dir, problem_id)

        if not binary_path.exists():
            print_color(f"❌ 二进制文件 {binary_path} 不存在，跳过评测。", RED)
            continue

        if not testcases:
            print_color(f"⚠️ 题目 {problem_id} 没有找到有效的测试用例，跳过。", YELLOW)
            continue

        summary = evaluate_testcases(problem_id, binary_path, testcases)
        total_summary["AC"] += summary["AC"]
        total_summary["WA"] += summary["WA"]

    # 输出最终汇总
    total_tests = total_summary["AC"] + total_summary["WA"]
    print_color("\n🏆 总评测结果:", BLUE)
    print_color(
        f"🎯 总计 {total_tests} 测试用例，{total_summary['AC']} AC, {total_summary['WA']} WA",
        GREEN if total_summary["WA"] == 0 else RED,
    )


if __name__ == "__main__":
    main()
