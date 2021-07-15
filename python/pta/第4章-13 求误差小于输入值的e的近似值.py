#第4章-13 求误差小于输入值的e的近似值
episilon = float(input())
def factory(n):
    if n==0 or n==1:
        return 1
    else :
        return n*factory(n-1)
e = 0
i = 0
single = 1/factory (i)
while True:
    e+=single
    if single >= episilon:
        i+=1
        single = 1/factory(i)
    else :
        break
print("{:.6f}".format(e))
    