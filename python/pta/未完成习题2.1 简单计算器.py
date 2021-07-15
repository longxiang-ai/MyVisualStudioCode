line = input()
nums =[]
print(line)
def isop(char):
    if char == '-' or char == '+' or char == '*' or char == '/':
        return True
    else:
        return False
def isnum(char):
    if char>='0' and char<='9':
        return True
    else:
        return False
for i in range (len(line)):
    if isnum(line[i]):
        down = 0
        for j in range(i,len(line)):
            if isnum(line[j])==False:
                down = j
                break
        #nums.append(int(line[i:down]))
        #print(line[i:down])
        if len(line[i:down])>0:
            print(int(line[i:down]))
            i+=len(line[i:down])+1

        
