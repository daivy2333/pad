#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;

        int max_left = 0, max_right = 0;
        int result = 0;
        
        while(left < right)
        {
            if(max_left < height[left]) max_left = height[left];
            if(max_right < height[right]) max_right = height[right];

            if(height[left] < height[right])
            {
                result += max_left - height[left];
                left++;
            }
            else
            {
                result += max_right - height[right];
                right--;
            }
        }
        return result;
    }
};