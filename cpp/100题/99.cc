#include "main.h"
class Solution {
public:
    int findKOr(vector<int>& nums, int k) {
        vector<int> arr(32,0);
        for(auto i: nums)
        {
            int index = 0;
            while(i)
            {
                arr[index++] += i&1;
                i >>= 1;
            }
        }
        int index;
        for(int i=31; i>=0; i--)
        {
            if(arr[i] != 0)
            {
                index = i;
                break;
            }
        }
        int res = 0;
        for(int i=0; i<= index; i++)
        {
            if(arr[i] >= k)
            {
                res += 1<<i;
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> m1 = {7,12,9,8,9,15};
    vector<int> m2 = {2,12,1,11,4,5};
    vector<int> m3 = {10,8,5,9,11,6,8};
    cout<< s.findKOr(m1,4)<< endl;
    cout<< s.findKOr(m2,6)<< endl;
    cout<< s.findKOr(m3,1)<< endl;
    return 0;
}