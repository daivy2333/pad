#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        int len = s.size();
        int left=0, road=0;
        unordered_map<char, int> map;
        for(int right=0; right<len; right++)
        {
            char in = s[right];
            map[in]++;

            while(map.size()==3)
            {
                road += len-right;
                char out = s[left++];
                map[out]--;
                if(!map[out]) map.erase(out);
            }
        }
        return road;
    }
};