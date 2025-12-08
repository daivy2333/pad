#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        int sub;
        for(int i = 0; i < nums.size(); i++)
        {
            sub = target - nums[i];
            if(map.find(sub) != map.end())
            {
                return {map[sub],i};
            }
            else
            {
                map[nums[i]] = i;
            }
        }
        return {};
    }
};

int main()
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> res = s.twoSum(nums,target);
    for(auto i : res)
    {
        cout << i << " ";
    }
    cout<<endl;
    return 0;
}