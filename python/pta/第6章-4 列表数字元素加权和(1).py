lst = eval(input())
def flat(nums,depth=1):
    res = []
    for i in nums:
        if isinstance(i, list):#如果这个变量是list
            res.extend(flat(i,depth+1))#那么通过递归方法把它附在后面
        else:
            res.append(i*depth)
    return res
output=flat(lst)
print(sum(output))