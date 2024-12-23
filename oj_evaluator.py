import os
import subprocess
import argparse
import sys
import json
import yaml
import psutil  # 获取内存使用信息
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
    parser.add_argument(
        "--config",
        default="./config.yaml",
        help="指定配置文件路径，支持 JSON 和 YAML 格式，默认 ./config.yaml",
    )
    return parser.parse_args()


def load_config(config_path):
    """加载配置文件 (支持 JSON 和 YAML)"""
    config_path = Path(config_path)
    if not config_path.exists():
        print_color("⚠️ 未找到配置文件，将使用默认配置。", YELLOW)
        return {}

    try:
        if config_path.suffix == ".json":
            with open(config_path, "r") as f:
                return json.load(f)
        elif config_path.suffix in [".yaml", ".yml"]:
            with open(config_path, "r") as f:
                return yaml.safe_load(f)
    except Exception as e:
        print_color(f"❌ 配置文件加载失败: {e}", RED)
        return {}


def get_problem_config(config, problem_id):
    """获取单个题目的配置，优先级：特定题目 > 全局配置 > 默认配置"""
    default_config = {
        "time_limit": 5,
        "memory_limit": 256,  # 单位 MB
        "max_attempts": 1,
        "output_diff": True,
    }
    global_config = config.get("global", {})
    problem_config = config.get(str(problem_id), {})

    final_config = default_config.copy()
    final_config.update(global_config)
    final_config.update(problem_config)

    return final_config


def find_binary(problem_id, binary_dir):
    """找到二进制文件"""
    binary_name = f"homework_{problem_id}"
    binary_path = Path(binary_dir) / binary_name
    if os.name == "nt":
        binary_path = binary_path.with_suffix(".exe")
    return binary_path


def get_testcases(testcases_dir, problem_id):
    """获取测试用例的输入输出文件，并按字典序排序"""
    problem_dir = Path(testcases_dir) / problem_id
    if not problem_dir.exists():
        return []

    testcases = []
    for file in problem_dir.glob("*-in.txt"):
        input_file = file
        output_file = file.with_name(file.name.replace("-in.txt", "-out.txt"))
        if output_file.exists():
            testcases.append((input_file, output_file))

    # 按文件名字典序排序
    testcases.sort(key=lambda x: x[0].name)
    return testcases


def compile_and_run(binary_path, input_file, time_limit):
    """运行二进制程序并获取输出，同时监控内存使用"""
    try:
        with open(input_file, "r") as infile:
            process = subprocess.Popen(
                [str(binary_path)],
                stdin=infile,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )
            ps_process = psutil.Process(process.pid)
            peak_memory = 0

            while process.poll() is None:
                try:
                    memory_usage = ps_process.memory_info().rss / (1024 * 1024)  # MB
                    peak_memory = max(peak_memory, memory_usage)
                except psutil.NoSuchProcess:
                    break

            stdout, stderr = process.communicate(timeout=time_limit)
            returncode = process.returncode

            if returncode != 0:
                return None, f"Runtime Error (Exit Code: {returncode})", peak_memory

            return stdout.strip(), stderr.strip(), peak_memory

    except subprocess.TimeoutExpired:
        process.kill()
        return None, "Time Limit Exceeded (TLE)", peak_memory
    except Exception as e:
        return None, f"Runtime Error: {e}", 0


def evaluate_testcases(problem_id, binary_path, testcases, config):
    """评测所有测试用例"""
    summary = {"AC": 0, "WA": 0, "RE": 0, "TLE": 0, "MLE": 0}
    time_limit = config["time_limit"]
    memory_limit = config["memory_limit"]

    print_color(f"\n🚀 开始评测题目 {problem_id}...", GREEN)

    for i, (input_file, output_file) in enumerate(testcases, 1):
        print_color(f"🧪 测试用例 {i}: {input_file.name}", BLUE)
        user_output, error_output, peak_memory = compile_and_run(
            binary_path, input_file, time_limit
        )

        # 读取输入用例内容，用于错误时显示
        with open(input_file, "r") as f:
            input_content = f.read().strip()

        if error_output == "Time Limit Exceeded (TLE)":
            print_color(f"❌ 超时 (TLE)", RED)
            print_color(f"  时间限制: {time_limit}s", RED)
            print_color(f"  输入:", RED)
            print_color(f"  {input_content}", RED)
            summary["TLE"] += 1
            continue

        if "Runtime Error" in error_output:
            print_color(f"❌ 运行时错误 (RE):", RED)
            print_color(f"  错误信息: {error_output}", RED)
            if user_output and user_output.strip():
                print_color("  标准输出 (stdout):", RED)
                print_color(f"  {user_output}", RED)
            if error_output and error_output.strip():
                print_color("  错误输出 (stderr):", RED)
                print_color(f"  {error_output}", RED)
            print_color(f"  输入:", RED)
            print_color(f"  {input_content}", RED)
            summary["RE"] += 1
            continue

        if peak_memory > memory_limit:
            print_color(f"❌ 内存超限 (MLE):", RED)
            print_color(f"  内存限制: {memory_limit} MB", RED)
            print_color(f"  实际使用: {peak_memory:.2f} MB", RED)
            print_color(f"  输入:", RED)
            print_color(f"  {input_content}", RED)
            summary["MLE"] += 1
            continue

        with open(output_file, "r") as f:
            expected_output = f.read().strip()

        if user_output == expected_output:
            print_color("✅ 测试用例通过 (AC)", GREEN)
            summary["AC"] += 1
        else:
            print_color("❌ 输出错误 (WA):", RED)
            print_color("  输入:", RED)
            print_color(f"  {input_content}", RED)
            print_color("  预期输出:", RED)
            print_color(f"  {expected_output}", RED)
            print_color("  实际输出:", RED)
            print_color(
                f"  {user_output if user_output is not None else '<无输出>'}", RED
            )
            summary["WA"] += 1

    return summary


def main():
    args = parse_args()
    config = load_config(args.config)
    testcases_dir = Path(args.testcases_dir)
    binary_dir = Path(args.binary_dir)

    total_summary = defaultdict(int)

    for problem_id in args.ids or [
        p.name for p in testcases_dir.iterdir() if p.is_dir()
    ]:
        problem_config = get_problem_config(config, problem_id)
        binary_path = find_binary(problem_id, binary_dir)
        testcases = get_testcases(testcases_dir, problem_id)
        summary = evaluate_testcases(problem_id, binary_path, testcases, problem_config)
        for k, v in summary.items():
            total_summary[k] += v


if __name__ == "__main__":
    main()
