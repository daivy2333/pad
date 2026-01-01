#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        int len = s.size();
        int map[2]{};
        int left=0, result=0;
        for(int right=0; right<len; right++)
        {
            int in = s[right]=='1'?1:0;
            map[in]++;

            while(map[1]>k&&map[0]>k)
            {
                int out = s[left++]=='1'?1:0;
                map[out]--;
            }

            result += right-left+1;
        }
        return result;
    }
};