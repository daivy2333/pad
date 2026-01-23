#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int len = prices.size();
        stack<int> st;
        vector<int> res = prices;
        for(auto i = len-1; i >= 0; i--)
        {
            int& cur = res[i];
            while(!st.empty() && cur < st.top())
            {
                st.pop();
            }
            if(!st.empty())
            {
                cur -= st.top();
            }
            st.push(prices[i]);
        }
        return res;
    }
};