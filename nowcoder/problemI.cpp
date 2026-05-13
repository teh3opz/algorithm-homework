class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        //栈里存柱子的下标，保证高度递增
        vector<int> st;
        for (int i = 0; i <= n; i++) {
            //最后补一个高度为0的柱子，用来清空栈
            int cur = (i == n ? 0 : heights[i]);
            //当前柱子更矮，说明栈顶柱子的最大面积可以确定
            while (!st.empty() && heights[st.back()] > cur) {
                int h = heights[st.back()];
                st.pop_back();
                //左边界是新的栈顶，右边界是当前位置i
                int left = st.empty() ? -1 : st.back();
                int width = i - left - 1;
                ans = max(ans, h * width);
            }
            st.push_back(i);
        }
        return ans;
    }
};
