#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int len = nums.size();
        int left=0, road=0, result=len+1;
        for(int right=0; right<len; right++)
        {
            int in = nums[right];
            road += in;

            while(road-nums[left]>=target)
            {
                int out = nums[left];
                road -= out;
                left++;
            }
            if(road>=target)result = min(result, right-left+1);
        }
        return result<=len? result:0;
    }
};