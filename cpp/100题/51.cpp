#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool judgeSquareSum(int c) {
        for(int i = 0; i*i <= c/2; i++)
        {
            int b = sqrt(c - i*i);
            if(i*i + b*b == c) return true;
        }
        return false;
    }
};