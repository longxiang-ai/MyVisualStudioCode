n = int(input())
count = 0


def pr(five, two, one):
    print("fen5:{}, fen2:{}, fen1:{}, total:{}".format(
        five, two, one, five+two+one))


def change(five, two, one, n):
    global count
    if five < 1 or two < 1 or one < 1:
        return
    else:
        pr(five, two, one)
        count += 1
        if five > 1:
            change(five-1, two+2, one+1, n)
        else:
            if two > 1:
                change(five, two-1, one+2, n)


five, two, one = n//5, (n % 5)//2, n-n//5*5-(n % 5)//2*2
if five != 0:
    if five > 1 and two == 0 or five > 1 and one == 0:
        five -= 1
        two += 2
        one += 1
    if two > 1 and one == 0:
        two -= 1
        one += 2
    change(five, two, one, n)
    #print(five,two, one, n)
print('count = {}'.format(count))
