#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        int key = 2;
        int window_end = key;
        for(int i=key; i<len; i++)
        {
            if(nums[i] != nums[window_end - key])
            {
                nums[window_end++] = nums[i];
            }
        }
        return min(window_end, len);
    }
};