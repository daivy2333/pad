#include <bits/stdc++.h>
#include <algorithm>
// 不需要 <ranges> 和 <bit>

using namespace std;

class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        // 使用传统的 std::sort
        sort(arr.begin(), arr.end(), [](int a,int b) {
            // 使用 GCC 内置函数 __builtin_popcount
            int countA = __builtin_popcount(a);
            int countB = __builtin_popcount(b);
            // 如果二进制1的个数不同，按个数排；如果相同，按数值大小排
            if (countA != countB) {
                return countA < countB;
            }
            return a < b;
        });
        return arr;
    }
};
