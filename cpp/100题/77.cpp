#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1); // 结果初始化为 -1
        stack<int> st;          // 栈里存的是下标

        // 遍历长度翻倍，模拟循环
        for (int i = 0; i < 2 * n; i++) {
            // 取模运算获取当前实际数字
            int num = nums[i % n];

            // 核心逻辑：如果当前数字比栈顶下标对应的数字大
            // 说明栈顶元素的“下一个更大元素”找到了！
            while (!st.empty() && num > nums[st.top()]) {
                res[st.top()] = num; // 记录答案
                st.pop();            // 弹出栈顶，继续检查下一个
            }

            // 只有在遍历前半段（0 到 n-1）时才压栈
            // 这样每个元素只入栈一次，防止重复计算
            if (i < n) {
                st.push(i);
            }
        }
        return res;
    }
};
// 翻倍取模来模拟循环，你就学吧，以及不要思维僵化，进栈的不一定是被处理数据