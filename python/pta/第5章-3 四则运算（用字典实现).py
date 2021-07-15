a = int(input())
char = input()
b = int(input())
if char == '/' and b == 0:
    print("divided by zero")
else:
    dict = {"+": a+b, "-": a-b, "/": a/b, "*": a*b}
    print('{:.2f}'.format(dict[char]))
