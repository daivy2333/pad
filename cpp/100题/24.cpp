#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<char, int> map;
        int left = 0, result = 0, road = 0;
        for(int i=0; i<s.size(); i++)
        {
            map[s[i]]++;
            road++;

            while(map[s[i]]>2)
            {
                map[s[left++]]--;
                road--;
            }
            result = max(result, road);
        }

        return result;
    }
};