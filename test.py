from colorama import init, Fore, Style

success = True
cnt = 0
line = 0

init()

with open("io/expect.txt", "r") as expect:
    with open("io/output.txt", "r") as output:
        for (e, o) in zip(expect, output):
            line = line + 1
            e = e.rstrip()
            o = o.rstrip()
            if e != o:
                print(f"第{line}行发现不同!")
                print(f"预期输出: {e}")
                print(f"实际输出: {o}")
                success = False
                cnt = cnt + 1

if success:
    print(Fore.GREEN + "通过测试!" + Style.RESET_ALL)
else:
    print(Fore.RED + f"未通过测试, 共找到{cnt}个不同!" + Style.RESET_ALL)
