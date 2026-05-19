"""
问题描述：
给定一个包含不同整数元素的数组 A[1..n]，并且满足：A[1] > A[2]，且 A[n-1] < A[n]。如果某个元素比它两边的邻居元素都小，即 A[x] < A[x-1] 且 A[x] < A[x+1]，那么称 A[x] 是一个局部最小值。 
要求设计一个 O(log n) 时间复杂度的算法，找到数组中的一个局部最小值，并返回该局部最小值及其下标。
算法分析：
由于数组元素互不相同，并且满足 A[1] > A[2]、A[n-1] < A[n]，可以保证数组中至少存在一个局部最小值。用二分查找思想：取中间位置 mid。
如果A[mid]同时小于左右两个相邻元素，则 A[mid] 就是局部最小值。
如果A[mid] > A[mid-1]，说明从mid向左存在下降趋势，因此左半部分一定存在局部最小值。
如果A[mid] > A[mid+1]，说明从mid向右存在下降趋势，因此右半部分一定存在局部最小值。
每次判断后都可以舍弃一半区间，因此时间复杂度为 O(log n)。
"""
def findLocalMin(A):
    n = len(A)
    #如果数组长度不足3，无法按照题目中“两边邻居”的定义判断
    if n < 3:
        return None, None
    left = 1
    right = n - 2
    while left <= right:
        mid = (left + right) // 2
        #如果mid位置比左右邻居都小，则找到局部最小值
        if A[mid] < A[mid - 1] and A[mid] < A[mid + 1]:
            return A[mid], mid + 1  # 返回值和第几位，下标按题目从1开始
        #如果左边更小，说明左半部分存在局部最小值
        elif A[mid] > A[mid - 1]:
            right = mid - 1
        #如果右边更小，说明右半部分存在局部最小值
        else:
            left = mid + 1
    return None, None
#测试
A = [9, 3, 7, 2, 1, 4, 5]
value, index = findLocalMin(A)
print(f"局部最小元素为: {value}, 位置为: {index}")
