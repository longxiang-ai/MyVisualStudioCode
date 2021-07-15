class Solution:
    def majorityElement(self, nums):
        nums.sort()
        return (nums[len(nums)//2])

s=Solution()
print(s.majorityElement([2,2,1,1,1,2,2]))