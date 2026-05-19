"""
第一问问题描述：
给定一个包含n个不同数字的数组arr，要求找到其中最小的k个数字，并按顺序输出它们。
算法分析：
先对整个数组进行排序，排序完成后数组前k个元素就是最小的k个数字。即按顺序输出直接输出排序后数组的前k个元素。
使用Python内置排序进行排序，此方法的平均时间复杂度为 O(nlogn)。
时间复杂度：O(n log n)
空间复杂度：O(1) 或 O(n)，取决于排序实现
"""
def findKSmallestBySorting(arr, k):
    arr.sort()
    return arr[:k]
#测试
arr = [5, 4, 3, 2, 6, 1, 88, 33, 22, 107]
k = 3
result = findKSmallestBySorting(arr, k)
print(f"前{k}个最小数据为: {result}")

"""
第二问问题描述：
给定一个包含n个不同数字的数组arr，要求建立一个包含这n个数字的最小堆，然后调用k次Extract-Min操作，每次取出当前堆中的最小值，最终得到前k个最小数字。
算法分析：
首先将数组建成最小堆，建堆的时间复杂度为O(n)。然后执行k次Extract-Min操作，每次取出堆顶最小元素，并重新调整堆结构。
每次Extract-Min的时间复杂度为O(logn)，因此k次操作的时间复杂度为O(klogn)。
时间复杂度：O(n+klogn)
空间复杂度：O(n)
"""
import heapq
def findKSmallestByHeap(arr, k):
    heap = arr[:]
    heapq.heapify(heap)
    result = []
    for _ in range(k):
        result.append(heapq.heappop(heap))
    return result
#测试
arr = [5, 4, 3, 2, 6, 1, 88, 33, 22, 107]
k = 3
result = findKSmallestByHeap(arr, k)
print(f"前{k}个最小数据为: {result}")
