sum = 0
n = int(input())
for i in range(2, n+1):
    sum = (sum+3) % i
print(sum+1)
