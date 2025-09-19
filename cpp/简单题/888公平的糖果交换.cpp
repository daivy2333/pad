class Solution {
public:
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        int sumA = accumulate(aliceSizes.begin(), aliceSizes.end(), 0);
        int sumB = accumulate(bobSizes.begin(), bobSizes.end(), 0);
        int delta = (sumA - sumB) / 2;
        unordered_set<int> rec(aliceSizes.begin(), aliceSizes.end());
        vector<int> ans;
        for (auto& y : bobSizes) {
            int x = y + delta;
            if (rec.count(x)) {
                ans = vector<int>{x, y};
                break;
            }
        }
        return ans;
    }
};
/*
哈希集合练习，这道题本身就是第一题的解决方法，就是实现这一块，要熟悉哈希集合的性质和函数接口才能流畅写出来
*/