#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        int len = words.size();
        if (words.empty()) return {};
        vector<string> res = { words[0] };
        for(int right=1; right<len; right++)
        {
            int left = right-1;
            if(to_int(words[left], words[right]))
            {
                continue;
            }
            else
            {
                res.push_back(words[right]);
            }

        }
        return res;
    }
private:
    int to_int(string l, string r)
    {
        unordered_map<char, int> map1;
        unordered_map<char, int> map2;

       for(char ch : l)
       {
        map1[ch]++;
       }
       for(char ch : r)
       {
        map2[ch]++;
       }
        return map1 == map2;
    }
};