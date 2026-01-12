#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int left = 0, right = s.size() - 1;
        
        while(left<right)
        {
            while(left<right)
            {
                if(vowels.count(s[right])) break;
                right--;
            }
            while(left<right)
            {
                if(vowels.count(s[left])) break;
                left++;
            }

            if(left<right) swap(s[left++], s[right--]); //关键是这一句，假如是奇数个的，最后两个指针会重在一起
        }
        
        return s;
    }
};
