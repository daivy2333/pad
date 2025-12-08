#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        if (nums.empty()) return 0;

        unordered_map<int,vector<int>> map;
        sort(nums.begin(),nums.end());

        int vec = 0,max_length = 1;
        map[vec] = {nums[0]};
        for(auto i = 1; i < nums.size(); i++)
        {

            if(nums[i] - nums[i-1] == 1)
            {
                map[vec].push_back(nums[i]);
            }
            else if(nums[i] == nums[i-1]) continue;
            else
            {
                vec++;
                map[vec] = {nums[i]};
            }
            int cur_len = map[vec].size();
            max_length = max(max_length, cur_len);
        }
        return max_length;
    }
};



/*
优化后
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        sort(nums.begin(), nums.end());

        int maxLength = 1;
        int currentLength = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1]) {
                // 跳过重复元素
                continue;
            } else if (nums[i] == nums[i-1] + 1) {
                // 连续：延长当前序列
                currentLength++;
                maxLength = max(maxLength, currentLength);
            } else {
                // 不连续：重置当前序列
                currentLength = 1;
            }
        }

        return maxLength;
    }
};

*/