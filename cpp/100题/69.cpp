#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while(left<=right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] < 0) left = mid+1;
            else right = mid-1;
        }
        int res = left;

        left = 0, right = nums.size()-1;
        while(left<=right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] <= 0) left = mid+1;
            else right = mid-1;
        }
        res = max((int)(nums.size()-left), res);

        return res;
    }
};