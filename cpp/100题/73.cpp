#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        int span = n / 4; // 计算四分之一的长度
        
        // 遍历数组，只需要遍历到 n - span 的位置
        for (int i = 0; i + span < n; i++) {
            // 如果当前位置的数和它向后 span 位置的数相同
            // 说明这个数至少出现了 span + 1 次，即超过 25%
            if (arr[i] == arr[i + span]) {
                return arr[i];
            }
        }
        
        return -1; // 题目保证一定存在，理论上不会执行到这里
    }
};
