import subprocess
import random
import sys
import time

num_tests = 10000
range_max = 1e6

while True:
    with open("input.txt", "w") as f:
        f.write(f"{num_tests}\n")

        for _ in range(num_tests):
            a = random.randint(1, range_max)
            b = random.randint(1, range_max)
            f.write(f"{a} {b}\n")

    start = time.perf_counter()
    with open("output1.txt", "w") as f:
        subprocess.run(["./task_schedule.exe"], stdin=open("input.txt", "r"), stdout=f)
    end = time.perf_counter()
    print(f"Program 1 execution time: {(end - start) * 1000} milliseconds")

    start = time.perf_counter()
    with open("output2.txt", "w") as f:
        subprocess.run(
            ["./task_schedule_v2.exe"], stdin=open("input.txt", "r"), stdout=f
        )
    end = time.perf_counter()
    print(f"Program 2 execution time: {(end - start) * 1000} milliseconds")

    with open("output1.txt", "r") as f1, open("output2.txt", "r") as f2:
        output1 = f1.read()
        output2 = f2.read()

        if output1 != output2:
            print("\033[91m" + "Outputs Differ!" + "\033[0m")
            break
        else:
            print("\033[92m" + "Test Passed!" + "\033[0m")
