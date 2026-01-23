#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int len = s.size();
        int key = 0;
        string res;
        for(int i=0; i<len; i++)
        {
            if(key<spaces.size() && i==spaces[key])
            {
                res.push_back(' ');
                key++;
            }
            res.push_back(s[i]);
        }
        return res;
    }
};