#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res (2, -1);
        int len = nums.size();
        if(nums.empty()) return res;

        int left = 0, right = len-1;
        while(left<=right)
        {
            int mid = left+(right-left)/2;
            if(nums[mid] >= target)
            {
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }

        if(left<nums.size() && nums[left] == target)
        {
            res[0] = left;
        }
        else
        {
            return res;
        }

        right = len-1;
        while(left<=right)
        {
            int mid = left+(right-left)/2;

            if(nums[mid] <= target)
            {
                left = mid+1;
            }
            else
            {
                right = mid-1;
            }
        }
        res[1] = right;

        return res;
    }
};