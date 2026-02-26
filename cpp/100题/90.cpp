#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestNumber(int n) {
        while(1)
        {
            if(!(n&(n+1))) return n;
            n++;
        }
    }
};

int main()
{
    Solution s;
    cout<< s.smallestNumber(5) << endl;
    return 0;
}