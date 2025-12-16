#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; ++i) {
            // 跳过重复的 nums[i]
            if (i > 0 && nums[i] == nums[i - 1]) 
                continue;

            // 若当前最小三数之和 > 0，后面不可能有解（已排序）
            if (nums[i] + nums[i + 1] + nums[i + 2] > 0) 
                break;

            // 若当前最大三数之和 < 0，跳过当前 i，尝试更大的
            if (nums[i] + nums[n - 2] + nums[n - 1] < 0) 
                continue;

            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0) {
                    ++left;
                } else if (sum > 0) {
                    --right;
                } else {
                    // 找到一组解
                    result.push_back({nums[i], nums[left], nums[right]});
                    // 跳过重复的 left 和 right
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    // 移动到下一个不同元素
                    ++left;
                    --right;
                }
            }
        }
        return result;
    }
};