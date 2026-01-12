#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int left = 0, right = s.size()-1;
        while(left<right && s[left]==s[right])
        {
            char note = s[left];
            while(left<=right && s[left]==note) left++;
            while(left<=right && s[right]==note) right--;
        }
        return right-left+1;
    }
};

//剥开字符串没什么难度，但是设置判定不同在最外层一旦left与right不同就会结算，这很牛的设计