class Solution:
    def isMonotonic(self, A):
        up=True
        down=True
        if len(A)==1:
            return True
        for i in range (0,len(A)-1):
            if A[i]<A[i+1]:
                down =False
            if A[i]>A[i+1]:
                up  =False
        return up or down

s=Solution()
print(s.isMonotonic([1,3,2]))
