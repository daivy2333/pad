#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int slow = len-1;
        for(int fast=len-1; fast>=0; fast--)
        {
             cout<<fast<<" "<<slow<< endl;
            if(nums[fast] == val)
            {
                swap(nums[fast], nums[slow]);
                slow--;
            }
        }
         cout<<len<<" "<<slow<<endl;
        return slow+1;
    }
};
int main()
{
    Solution s;
    vector<int> m = {0,1,2,2,3,0,4,2};
    int val = 3;
    cout<<s.removeElement(m,val)<<endl;
}