#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i]%2==0)
            {
                nums[i] = 0;
            }
            else if(nums[i]%2==1)
            {
                nums[i] = 1;
            }
            
        }
        for(auto i : nums)
        {
            cout<< i <<" ";
        }
        cout<<endl;
        sort(nums.begin(), nums.end());
        return nums;
    }
};

int main()
{
    Solution s;
    vector<int> m = {1,5,1,4,2};
    int val = 3;
    
    for(auto i : s.transformArray(m))
    {
        cout<< i << " ";
    }
    cout<<endl;
    return 0;
}