#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string reverseStr(string s, int k) {
        int len = s.size();
        for(int i=0; i<len; i+=k*2)
        {
            reverse(s.begin()+i, s.begin()+min(i+k,len));
        }
        return s;
    }
};