#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i=2; i<len; i++)
        {
            int left = 0;
            int right = i-1;

            while(left<right)
            {
                int note = nums[left]+nums[right];
                if(note > nums[i])
                {
                    res += right-left;
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
        return res;
    }
};