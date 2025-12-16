#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        
        if(s.size() < p.size()) return result;

        vector<int> count(26, 0);
        for(char c: p)
        {
            count[c - 'a']++;
        }

        vector<int> window(26,0);
        for(int i = 0; i < s.size(); i++)
        {
            window[s[i] - 'a']++;
            if(i >= p.size())
            {
                window[s[i - p.size()] - 'a']--;
            }
            if(window == count)
            {
                result.push_back(i - p.size() + 1);
            }
        }
        return result;
    }
};