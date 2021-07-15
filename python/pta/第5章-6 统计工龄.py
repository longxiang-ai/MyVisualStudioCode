n = int(input())
age = list(map(int, input().split(" ")))
for i in range(51):
    if i in age:
        print('{}:{}'.format(i, age.count(i)))
