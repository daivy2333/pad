#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int len = nums.size();
        int road=0, left=0, result=0;
        unordered_map<int, int> map;
        for(int right=0; right<len; right++)
        {
            int in = nums[right];
            road++;
            map[in]++;

            while(map[in]>k)
            {
                road--;
                int out = nums[left++];
                map[out]--;
            }
            
            result = max(result, road);
        }
        return result;
    }
};