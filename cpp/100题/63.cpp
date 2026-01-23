#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int res = INT32_MAX;
        
        unordered_set<int> map;
        for(auto i : nums1)
        {
            map.insert(i);
        }
        for(auto i : nums2)
        {
            if(map.count(i))
            {
                res = min(res, i);
            }
        }
        res = res==INT32_MAX? -1:res;
        return res;
    }
};