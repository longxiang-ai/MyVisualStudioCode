lst = eval(input())
def flat(nums,depth=1):
    count=0 
    for i in nums:
        if isinstance(i, list):#如果这个变量是list
            count +=(depth+1)/depth*flat (i,depth+1)
        else:
            count +=1
    return count
output=flat(lst)
print(int(output))