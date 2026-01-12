#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> map;
        for(int i = 0; i < numbers.size(); i++)
        {
            if(map.count(numbers[i]))
            {
                return {map[numbers[i]]+1, i+1};
            }
            else
            {
                map[target-numbers[i]] = i;
            }
        }
        return {};
    }
};