#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 左闭右开
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // 求前缀和
        vector<int> pre_sum(n + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            pre_sum[i + 1] = pre_sum[i] + nums[i];
        }

        for (auto& x : queries) {
            // pre_sum中有先导0，所以要求出 >x 的第一个元素下标并-1
            x = lower_bound(pre_sum, x + 1) - 1;
        }
        return queries;
    }
};

// 这种贪心前缀和真是受益匪浅