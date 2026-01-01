#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int balancedString(string s) {
        unordered_map<char, int> map;
        int left=0, road=0, result=0, len=s.size();
        for(int right=0; right<len; right++)
        {
            char in = s[right];
            map[in]++;

            if(right%4==3)
            {
                road = 4-map.size();
            }
            while(right%4==3&&left!=right)
            {
                char out = s[left++];
                if(--map[out]==0)
                {
                    map.erase(out);
                }
            }

            result += road;
        }
        return result;
    }
};