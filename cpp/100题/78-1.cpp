#include<bits/stdc++.h>
using namespace std;

class StockSpanner {
    stack<pair<int, int>> st;
    int num;
public:
    StockSpanner() {
        num = 0; 
    }
    
    int next(int price) {
        num = 1;
        while(!st.empty() && st.top().second<=price)
        {
            num += st.top().first;
            st.pop();
        }
        st.push({num, price});
        return num;
    }
};