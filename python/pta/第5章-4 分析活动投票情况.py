l = list(map(int, input().split(',')))
output = []
for i in range(6, 11):
    if i not in l:
        output.append(i)
print(*output, sep=' ')
