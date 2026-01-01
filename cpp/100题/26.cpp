#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int max_save = 0, left = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (1LL * nums[left] * k < nums[i]) {
                left++;
            }
            max_save = max(max_save, i - left + 1);
        }
        return nums.size() - max_save;
    }
};
