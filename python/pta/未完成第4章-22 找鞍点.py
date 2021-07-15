n =int (input())
matrix = []
for i in range(n):
    string = input().split(' ')
    matrix.append(string.copy())
for i in range(n):
    for j in range(n):
        matrix[i][j]=int(matrix[i][j])
max = []
min = []
for i in range(n):
    thismax = [matrix[i][0],0]
    for j in range(n):
        if matrix[i][j]>thismax[0]:
            thismax[0]=matrix[i][j]
            thismax[1]=i
    min.append(thismax.copy())
for i in range(n):
    thismin = [matrix[0][i],0]
    for j in range(n):
        if matrix[j][i]<thismin[0]:
            thismin[0]=matrix[j][i]
            thismin[1]=j
    min.append(thismin.copy())
for i in range(len(max)):
    if max[i][0]==min[i][0]:
        print(max[i][1],min[i][1])
        break
print(matrix)
