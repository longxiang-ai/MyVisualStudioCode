def fib(n):
    if n == 1 or n == 2:
        return 1
    else:
        return fib(n-1)+fib(n-2)


num = int(input())
i = 1
while True:
    if fib(i) > num:
        break
    else:
        i += 1
print(fib(i))
