#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
class Solution {
public:
    int binaryGap(int n) {
        bool note = false;
        int count , res = 0;
        while(n)
        {
            int key = n&1;
            if(key == 1)
            {
                if(!note) note = true;
                else res = max(count+1, res);
 
                count = 0;
            }
            else
            {
                if(note)count++;
            }
            n >>= 1;
        }
        return res;
    }
};
int main()
{
    Solution s;
    cout<<s.binaryGap(22)<<endl;
    return 0;
}