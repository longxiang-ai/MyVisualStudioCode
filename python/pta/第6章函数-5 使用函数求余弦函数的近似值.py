def factory(i):
    if i == 0 or i == 1:
        return 1
    else:
        return i*factory(i-1)


def funcos(eps, x):
    sum = 0.0
    i = 0
    while True:

        single = (-1)**(i) * (x)**(2*i) / factory(2*i)
        if abs(single) >= eps:
            sum += single
            i += 1
        else:
            break
    return sum


eps = float(input())
x = float(input())


value = funcos(eps, x)
print("cos({0}) = {1:.4f}".format(x, value))
