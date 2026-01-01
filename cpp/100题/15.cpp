#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int right = 0;
        int result = 0;
        int road = 0;
        for(right=0; right<arr.size(); right++)
        {
            int left = right-k+1;
            road += arr[right];
            while(left>=0 && right-left==k-1)
            {
                float av = road/k;
                if(av>=threshold) result++;

                road -= arr[left++];
            }
        }
        return result;
    }
};