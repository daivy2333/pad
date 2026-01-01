#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int len = nums.size();
        int left=0, road=1, result=0;
        if (k <= 1) {
            return 0;
        }
        for(int right=0; right<len; right++)
        {
            int in = nums[right];
            road *= in;

            while(road>=k)
            {
                int out = nums[left++];
                road /= out;
            }
            result += right-left+1;
        }
        return result;
    }
};