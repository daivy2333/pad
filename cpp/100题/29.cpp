#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_set<int> map;
        int road=0, result=0, left=0;
        for(int right=0; right<nums.size(); right++)
        {
            int in = nums[right];
            road += in;
            if(!map.count(in)) map.insert(in);
            else
            {
                while (map.count(in))
                {
                    road -= nums[left];
                    map.erase(nums[left++]);
                }
                map.insert(in);
            }
            result = max(result, road);
        }

        return result;
    }
};