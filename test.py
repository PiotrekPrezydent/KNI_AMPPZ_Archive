import subprocess
from pathlib import Path
import sys
import time
import argparse

class TerminalColors:
    RESET = "\033[0m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"
    CYAN = "\033[36m"
    WHITE = "\033[37m"
    GRAY = "\033[90m"

def print_colored(text, color):
    print(f"{color}{text}{TerminalColors.RESET}")

class ExecutionTime:
    def __enter__(self):
        self.start_time = time.time()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.end_time = time.time()
        self.execution_time = self.end_time - self.start_time
        print_colored(f"Execution time: {self.execution_time:.4f} seconds", TerminalColors.GRAY)

def compile_cpp(cpp_file: Path) -> Path:
    executable = cpp_file.with_suffix('.exe')
    compile_process = subprocess.run(['g++', cpp_file, '-o', executable], capture_output=True, text=True)
    if compile_process.returncode != 0:
        raise RuntimeError(f"Compilation error:\n{compile_process.stderr}")
    return executable

def compare_outputs(expected: str, actual: str, ignore_order: bool) -> bool:
    if ignore_order:
        return sorted(expected.split()) == sorted(actual.split())
    return expected == actual

def run_test(executable: Path, input_file: Path, output_file: Path, ignore_order: bool):
    with open(input_file, 'r') as f:
        input_data = f.read()

    with open(output_file, 'r') as f:
        expected_output = f.read().strip()

    with ExecutionTime():
        run_process = subprocess.run([executable], input=input_data, capture_output=True, text=True)
        if run_process.returncode != 0:
            raise RuntimeError(f"Runtime error:\n{run_process.stderr}")

    actual_output = run_process.stdout.strip()

    if compare_outputs(expected_output, actual_output, ignore_order):
        print_colored(f"{input_file.name} passed.", TerminalColors.GREEN)
    else:
        print_colored(f"{input_file.name} failed.", TerminalColors.YELLOW)
        print(f"Expected output:\n{expected_output}")
        print(f"Actual output:\n{actual_output}")

def test_all_cases(cpp_file: str, test_dir: str, ignore_order: bool):
    cpp_path = Path(cpp_file)
    test_path = Path(test_dir)

    if not cpp_path.is_file() or not test_path.is_dir():
        raise FileNotFoundError("Invalid C++ file or test directory.")

    executable = compile_cpp(cpp_path)

    try:
        input_files = sorted(test_path.glob("*.in"))
        
        if not input_files:
            print_colored(f"No tests found in {test_dir}", TerminalColors.YELLOW)
        else:
            for input_file in input_files:
                output_file = test_path / input_file.name.replace("in", "out")
                if output_file.is_file():
                    print_colored(f"Running test: {input_file.name}", TerminalColors.CYAN)
                    run_test(executable, input_file, output_file, ignore_order)
                else:
                    print_colored(f"Output file not found for {input_file.name}", TerminalColors.RED)
    
    finally:
        if executable.exists():
            executable.unlink()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Run C++ test cases with automated comparison.")
    parser.add_argument("cpp_file", type=str, help="Path to the C++ source file")
    parser.add_argument("test_directory", type=str, help="Path to the test cases directory")
    parser.add_argument("--ignore-order", action="store_true", help="Ignore order in output comparison")
    args = parser.parse_args()

    try:
        test_all_cases(args.cpp_file, args.test_directory, args.ignore_order)
    except Exception as e:
        print_colored(f"Error: {e}", TerminalColors.RED)
