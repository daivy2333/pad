#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        int slow = 0, fast;
        unordered_set<int> map;
        for(fast=0; fast<len; fast++)
        {
            if(!map.count(nums[fast]))
            {
                map.insert(nums[fast]);
                nums[slow++] = nums[fast];
            }
        }
        map.empty();
        return slow;
    }
};