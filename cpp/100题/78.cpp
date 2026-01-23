#include<bits/stdc++.h>
using namespace std;
class StockSpanner {
private:
    vector<int> map;
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        map.push_back(price);
        int len = map.size();
        int res = 0;
        for(int i=len-1; i>=0; i--)
        {
            if(map[i] > price) break;
            res++;
        }
        return res;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */