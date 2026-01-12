#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> result;
        int left=0, right=arr.size()-1;
        int a_l=abs(x-arr[left]),a_r=abs(x-arr[right]);
        while(right-left!=k-1)
        {
            if(a_l<=a_r)
            {
                right--;
                a_r=abs(x-arr[right]);
            }
            else
            {
                left++;
                a_l=abs(x-arr[left]);
            }
        }
        for(int i=left; i<=right; i++)
        {
            result.push_back(arr[i]);
        }
        return result;
    }
};
// 好吧，必须使差值相当的情况也尽可能往较小的地方缩小，这才能符合题意，没有就会偏大