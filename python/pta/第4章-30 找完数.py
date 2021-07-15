from math import sqrt
def isperfect(n):
    num = []
    max = int(sqrt(n))+1
    j=1
    while j<=max+1:
        if n%j ==0:
            num.append(j)
            if j!=1:
                num.append(n//j)
        j+=1
    num.sort()
    if sum(num) == n:
        print("{} = ".format(n), end='')
        first = 1
        for i in range(len(num)):
            if first == 0:
                print(' + ', end='')
            else:
                first = 0
            print(num[i], end='')
        print()
        return True
    else:
        return False


string = input().split(' ')
m = int(string[0])
n = int(string[1])
flag = 0
for i in range(m, n+1):
    if isperfect(i) == True:
        flag = 1
if flag == 0:
    print("None")
