#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int CurSum = nums[0];
        int MaxSum = nums[0];
        for(auto i=1; i<nums.size(); i++)
        {
            CurSum = max(nums[i], CurSum+nums[i]);
            MaxSum = max(MaxSum, CurSum);
        }

        return MaxSum;
    }
};