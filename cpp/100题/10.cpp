#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans=0, sum=0;
        unordered_map<int, int> m;
        m.insert({0, 1});
        for(int i=0; i<nums.size(); i++)
        {
            sum += nums[i];
            if(m.count(sum-k)) ans += m[sum-k];
            m[sum]++;
        }
        return ans;
    }
};