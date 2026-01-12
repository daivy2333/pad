#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int len = nums.size();
        if(len < 3) return res;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < len-2; i++)
        {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            if(nums[i] + nums[len-1] + nums[len-2] < 0) continue;
            int left = i+1;
            int right = len-1;
            while(left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum > 0)
                {
                    right--;
                }
                else if(sum < 0)
                {
                    left++;
                }
                else
                {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    ++left;
                    --right;
                }
            }
        }
        return res;
    }
};