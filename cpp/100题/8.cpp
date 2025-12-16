#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int ans = 0;
        unordered_set<char> set;
        
        for(int right = 0; right < s.size(); right++)
        {
            while(set.count(s[right]))
            {
                set.erase(s[left]);
                ++left;
            }
            set.insert(s[right]);
            ans = max(ans,right - left + 1);
        }
        return ans;
    }
};