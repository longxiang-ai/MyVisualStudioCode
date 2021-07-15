n =int(input())
grade =[]
for i in range (n):
    grade.append(list(input().split(" ")))
print(grade)
output =[]
for i in range (n//2):
    if grade[i][0]=="0":
        for j in range(n-1,0,-1):
            if grade[j][0]=="1" :
                output.append([grade[i][1],grade[j][1]])
                grade.remove(grade[j])
                j-=1
                break
    else :
        for j in range(n-1,0,-1):
            if grade[j][0]=="0" and [grade[j][1]] not in output:
                output.append([grade[i][1],grade[j][1]])
                grade.remove(grade[j])
                j-=1
                break
print(output)
