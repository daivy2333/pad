#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int map = 0;
        int left=0, road=0, result=0;
        for(int i=0; i<nums.size(); i++)
        {
            road++;
            int in = nums[i];
            if(in==0)
            {
                map++;
            }

            while(map>k)
            {
                int out = nums[left];
                if(out==0) map--;
                road--;
                left++;
            }

            result = max(result, road);
        }
        return result;
    }
};