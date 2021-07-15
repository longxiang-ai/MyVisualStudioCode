n, m = map(int, input().split())
sequence = list(map(int, input().split()))
print(sequence)
# 子序列中元素个数为[2,n]个
# 动态规划的方法解决寻找beautiful子列的问题
# 注意到，beautiful子列满足的条件：
# 在随意某处设置一个截断，要么左边是beautiful子列，要么右边是beautiful子列，要么截断处的左右两边恰好就是相邻元素
#
# 设子序列中元素个数为k(k>=2, k<=n)
# 如果已经有一个子列含k个元素，那么在此基础上添加一个元素，使其成为beautiful子列的情况有两种
# 1.其本身已经是beautiful子列
# 2.其本身不是beautiful 子列，但其最后一个元素和新加的元素满足条件
# 则 b[k+1] = b[k] + u_fit[k]
count = 0
for i in range(0, n):
    subsequence = sequence[i:i+2]
    for num in range (2,n+1):
        
    