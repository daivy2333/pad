#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> st;
        for(int i = n-1; i>=0; i--)
        {
            int t = temperatures[i];
            while(!st.empty() && t >= temperatures[st.top()])
            {
                st.pop();
            }

            if(!st.empty())
            {
                ans[i] = st.top() - i;

            }
            st.push(i);
        }
        return ans;
    }
};

// 理解何谓单调，单调栈的名字意味着什么？
// 就是一旦满足条件就会一直弹出直到不满足