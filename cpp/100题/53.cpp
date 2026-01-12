#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int len = nums.size();
        int res = 1000000;
        if(len < 3) return res;
        sort(nums.begin(), nums.end());
        for(int i=0; i<len-2; i++)
        {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            int left = i+1, right = len-1;
            while(left<right)
            {
                int sum = nums[i] + nums[left] + nums[right];

                if(sum > target)
                {
                    right--;
                    while(left < right && nums[left] == nums[left-1]) left++;
                }
                else if(sum < target)
                {
                    left++;
                    while(left < right && nums[left] == nums[left-1]) left++;
                }
                else
                {
                    return sum;
                }
                res = abs(sum - target) < abs(res - target) ? sum:res;
            }
        }
        return res;
    }
};