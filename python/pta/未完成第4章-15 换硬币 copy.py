n = int(input())
count = 0


def pr(five, two, one):
    global count
    if five > 0 and two > 0 and one > 0:
        print("fen5:{}, fen2:{}, fen1:{}, total:{}".format(
            five, two, one, five+two+one))
        count += 1


def change(five, two, one, n):
    print(five,two, one, n)
    if five == 0 and two == 0:
        return
    else:
        pr(five, two, one)
        if two > 1:
            change(five, two-1, one+2, n)
        if five > 1:
            print("Yes")
            # change(five-1,(n-(five-1)*5)//2, n-((n-(five-1)*5)//2*2), n)


five, two, one = n//5, (n % 5)//2, n-n//5*5-(n % 5)//2*2
change(five, two, one, n)
#print(five,two, one, n)
print('count = {}'.format(count))
