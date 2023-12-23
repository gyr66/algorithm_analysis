import os
import random
import subprocess


def generate_test_case():
    n = random.randint(1, 100)
    numbers_line1 = " ".join(str(random.randint(0, 100)) for _ in range(n))
    numbers_line2 = " ".join(str(random.randint(0, 100)) for _ in range(n + 1))
    with open("io/input.txt", "w") as f:
        f.write(f"{n}\n{numbers_line1}\n{numbers_line2}\n")


def run_program(executable):
    subprocess.run([executable])
    with open("io/output.txt", "r") as f:
        return f.read().strip()


def main():
    while True:
        generate_test_case()
        output_a = run_program("./a.exe")
        output_b = run_program("./b.exe")
        if output_a != output_b:
            print("不一致的测试用例已找到!")
            with open("io/input.txt", "r") as f:
                print("测试用例:")
                print(f.read())
            print("a.exe 的输出:")
            print(output_a)
            print("b.exe 的输出:")
            print(output_b)
            break
        else:
            print(f"{output_a} {output_b} 测试通过!")


if __name__ == "__main__":
    main()
