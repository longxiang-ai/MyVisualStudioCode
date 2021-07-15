string = input().split(' ')
matrix = []
for i in range (3):
    line = []
    for j in range (3):
        line.append(int(string[3*i+j]))
    matrix.append(line.copy())
final = []
for i in range (3):
    thisfinal=[]
    for j in range (3):
        thisfinal.append(matrix[j][i])
    final.append(thisfinal)
for i in range (3):
    for j in range(3):
        print('{:4}'.format(final[i][j]),end='')
    print()