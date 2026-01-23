#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(auto i: nums2)
        {
            nums1.push_back(i);
        }
        sort(nums1.begin(), nums1.end());
    }
};