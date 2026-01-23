#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int len = spells.size();
        sort(potions.begin(), potions.end());
        vector<int> res;
        for(auto i : spells)
        {
            res .push_back(sov(i, potions, success));
        }
        return res;
    }
private:

    int sov(int key, vector<int>& map, long long success)
    {
        int left = 0, right = map.size()-1;
        while(left<=right)
        {
            int mid = left + (right-left)/2;
            long long in = (long long)map[mid]*key;
            if(in >= success) right = mid-1;
            else left = mid+1;
        }
        return map.size() - left;
    }
};