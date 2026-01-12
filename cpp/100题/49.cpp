#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int len = arr.size();
        int left = 0, right = len - 1, key = 0;
        vector<int> res (k, 0);
        sort(arr.begin(), arr.end());
        int m = (len - 1) / 2, mid = arr[m];
        while(key < k)
        {
            int abs_l = abs(arr[left] - mid), abs_r = abs(arr[right] - mid);
            if ( (abs_r > abs_l) || ( (abs_r == abs_l) && (arr[right] > arr[left]) ) )
            {
                // 选右边
                res[key++] = arr[right];
                right--;
            }
            else
            {
                // 选左边
                res[key++] = arr[left];
                left++;
            }

        }
        return res;
    }
};
int main()
{
    vector<int> input = {1,2,3,4,5};
    Solution s;
    vector<int> output = s.getStrongest(input, 2);
    for(auto i : output)
    {
        cout<<i<<" ";
    }
}