# 第4章-16 jmu-python-判断是否构成三角形
string = input().split(" ")
a = int(string[0])
b = int(string[1])
c = int(string[2])
if a > 0 and b > 0 and c > 0 and a+b > c and a+c > b and b+c > a:
    print("yes")
else :
    print("no")
