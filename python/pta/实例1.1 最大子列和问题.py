n = int(input())
nums = list(map(int, input().split(" ")))



def maxx(nums, n):
    thissum = 0
    print(id(thissum))
    maxsum = 0
    print(id(maxsum))
    for i in range(n):
        thissum += nums[i]

        if thissum > maxsum:
            maxsum = thissum
            print(id(thissum))
            print(id(maxsum))
        if thissum < 0:
            thissum = 0
        print(id(thissum))
        print(id(maxsum))
    return maxsum
#print(int(maxsum))

print(maxx(nums, n))
