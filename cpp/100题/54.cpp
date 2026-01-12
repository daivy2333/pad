#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int purchasePlans(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        int mod = 1000000007;
        int left = 0, right = len-1;
        long long res = 0;
        while(left<right)
        {
            int sum = nums[left] + nums[right];
            if(sum <= target)
            {
                res = (right-left+res) % mod;
                left++;
            }
            else
            {
                right--;
            }
        }
        return (int)res;
    }
};