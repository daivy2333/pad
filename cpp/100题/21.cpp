#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        unordered_map<int, int> map;
        int ans = 0;

        for(int i=0; i<arrivals.size(); i++)
        {
            int& x = arrivals[i];

            if(map[x]==m)
            {
                x = 0;
                ans++;
            }
            else
            {
                map[x]++;
            }

            int left = i+1-w;
            if(left>=0)
            {
                map[arrivals[left]]--;
            }
        }

        return ans;
    }
};