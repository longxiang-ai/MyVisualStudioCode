n = int(input())
char = 'A'
for i in range(n,0,-1):
    for j in range(i):
        print('{:2}'.format(char),end='')
        char=chr(ord(char)+1)
    print()