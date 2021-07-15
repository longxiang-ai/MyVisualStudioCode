a, b = map(int, input().split(' '))
numset = set()
for i in range(a, b+1):
    if i % 3 == 0 and i % 5 == 0 and i % 7 == 0:
        numset.add(i)
print(len(numset))
