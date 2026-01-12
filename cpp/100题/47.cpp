#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int key = 0;
        for(auto i : nums)
        {
            nums[key++] *= i;
        }
        sort(nums.begin(), nums.end());
        return nums;
    }
};