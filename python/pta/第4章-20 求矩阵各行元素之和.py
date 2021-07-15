line = input().split(" ")
a = int(line[0])
b = int(line[1])
for i in range(a):
    sum = 0
    string = input().split(' ')
    for j in range(b):
        sum += int(string[j])
    print(sum)
