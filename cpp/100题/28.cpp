#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> map;
        int len = fruits.size();

        int left = 0, road = 0, result = 0;
        for(int right=0; right<len; right++)
        {
            road++;
            map[fruits[right]]++;

            while(map.size()>2)
            {
                road--;
                map[fruits[left]]--;
                if(map[fruits[left]]==0)
                {
                    map.erase(fruits[left]);
                }
                left++;
            }
            result = max(result, road);
        }
        return result;
    }
};