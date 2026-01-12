#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string reverseOnlyLetters(string s) {
        int left = 0, right = s.size()-1;

        while(left<right)
        {
            while(left<right)
            {
                if(isalpha(s[left])) break;
                left++;
            }
            while(left<right)
            {
                if(isalpha(s[right])) break;
                right--;
            }

            if(left<right) swap(s[left++], s[right--]);
        }
        
        return s;
    }
};