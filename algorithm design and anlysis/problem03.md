"""
问题描述：
给定数组profits，其中profits[i] 表示第i天股票的收益变化.正数表示上涨收益，负数表示下跌亏损。只能选择某一天买入，并选择未来某一天卖出一次。
买入到卖出期间的总收益等于这一段连续天数的收益之和,因此问题等价于：求profits数组中的最大连续子数组和，并返回该最大收益对应的买入日期和卖出日期。
算法分析：
采用线性扫描法,从左到右遍历数组，维护当前连续区间的收益和current_sum。
如果current_sum小于0，说明之前的连续收益会拖累后面的结果，因此从当前天重新开始计算，并更新当前买入日期。
如果current_sum 大于当前最大收益max_profit，就更新最大收益以及对应的买入日期和卖出日期。
时间复杂度：O(n)
"""
def maxProfit(profits):
    if not profits:
        return 0, None, None
    #当前连续区间的收益和
    current_sum = profits[0]
    #最大收益
    max_sum = profits[0]
    #当前区间起始下标
    current_start = 0
    #最大收益对应的买入和卖出下标
    buy_day = 0
    sell_day = 0
    for i in range(1, len(profits)):
        #如果前面的连续收益小于0，就从当前天重新开始
        if current_sum < 0:
            current_sum = profits[i]
            current_start = i
        else:
            current_sum += profits[i]
        #更新最大收益
        if current_sum > max_sum:
            max_sum = current_sum
            buy_day = current_start
            sell_day = i
    return max_sum, buy_day, sell_day
#测试
profits = [3, 2, 1, -7, 5, 2, -1, 3, -1]
max_profit, buy_day, sell_day = maxProfit(profits)
print(f"最大利润: {max_profit}, 买入日: 第{buy_day + 1}天, 卖出日: 第{sell_day + 1}天")
