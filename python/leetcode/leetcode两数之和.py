class Solution:
    def twoSum(self, nums, target):
        for i in range (len(nums)):
            for j in range (i,len(nums)):
                if nums[i]+nums[j]== target:
                    return [i,j]
s=Solution()
print(s.twoSum(nums = [2, 7, 11, 15], target = 9))