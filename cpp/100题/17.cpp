#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int right = 0, left = 0;
        int result = 100000000;
        int road = 0;
        for(right; right<blocks.size(); right++)
        {
            int note = blocks[right]=='W'?1:0;
            road += note;
            if(right-left==k-1)
            {
                int note = blocks[left]=='W'?1:0;
                result = min(result, road);
                road -= note;
                left++;
            }
        }
        return result;
    }
};