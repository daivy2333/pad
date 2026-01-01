#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int map = 0;
        int left = 0, road = 0, result = 0;
        for(int i=0; i<nums.size(); i++)
        {
            road += nums[i];
            if(nums[i]==0) map++;

            while(map>1)
            {
                if(nums[left]==0) map--;
                road -= nums[left++];
            }
            result = max(result, road);
        }
        result -= map==1?0:1;
        return result;
    }
};