#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int s[2]{}, max_s1 = 0;
        for (int i = 0; i < customers.size(); i++) {
            s[grumpy[i]] += customers[i];
            int left = i - minutes + 1; // 窗口左端点
            if (left < 0) { // 窗口长度不足 minutes
                continue;
            }
            max_s1 = max(max_s1, s[1]);
            // 窗口最左边元素离开窗口
            s[1] -= grumpy[left] ? customers[left] : 0;
        }
        return s[0] + max_s1;
    }
};
