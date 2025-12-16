#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;

        if(left == right) return 0;

        int Area = 0;

        while(left < right)
        {
            int curArea = (right-left) * min(height[left],height[right]);

            Area = max(Area, curArea);

            if(height[right] >= height[left]) left++;
            else right--;
        }
        return Area;
    }
};