#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int len = s.size();
        int start = 0;
        for(int i=0; i<=len; i++)
        {
            int right = i-1;
            int left = start;

            if(i==len || s[i]==' ')
            {
                while(right>left)
                {
                    swap(s[left++], s[right--]);
                }
                start = i+1;
            }
        }
        return s;
    }
};