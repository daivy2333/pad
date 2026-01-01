#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int len = s.size();
        vector<int> record;
        for(int i=0; i<len; i++)
        {
            record.push_back(abs(s[i]-t[i]));
        }
        int result = 0, road = 0, left = 0;;
        for(int right=0; right<len; right++)
        {
            road += record[right];

            while(road>maxCost)
            {
                road -= record[left++];
            }
            result = max(result, right-left+1);
        }
        return result;
    }
};