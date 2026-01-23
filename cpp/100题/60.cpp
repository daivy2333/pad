#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxKDistinct(vector<int>& nums, int k) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> res;
        unordered_set<int> map;
        for(int right=len-1; right>=0; right--)
        {
            if(nums[right]<0) break;
            // cout<< map.size() << endl;
            if(map.size() == k) break; 
            if(!map.count(nums[right]))
            {
                map.insert(nums[right]);
                res.push_back(nums[right]);
            }
        }
        return res;
    }
};
int main()
{
    Solution s;
    vector<int> m = {84,93,100,77,90};
    int val = 3;
    
    for(auto i : s.maxKDistinct(m, val))
    {
        cout<< i << " ";
    }
    cout<<endl;
    return 0;
}