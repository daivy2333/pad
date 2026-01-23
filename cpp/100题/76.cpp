#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int len = nums1.size();
        for(auto i=0; i<len; i++)
        {
            int& cur = nums1[i];
            cur = down(cur, nums2);
        }
        return nums1;
    }

private:
    int down(int& cur, vector<int>& nums)
    {
        stack<int> st;
        int len = nums.size();
        for(auto i=len-1; i>=0; i--)
        {
            if(cur==nums[i])
            {
               while(!st.empty() && cur > st.top())
                {
                    st.pop();
                }
                if(st.empty()) return -1;
                return st.top(); 
            }
            
            st.push(nums[i]);
        }
        return -1;
    }
};