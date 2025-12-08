#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    for(const auto& str : strs) {
        string sorted_str = str;  // 这里需要创建副本，因为要排序
        sort(sorted_str.begin(), sorted_str.end());
        map[sorted_str].push_back(str);  // 可以直接push_back，不需要检查是否存在
    }
    
    vector<vector<string>> result;
    result.reserve(map.size());  // 预分配空间，提高性能
    for(const auto& i : map) {
        result.push_back(i.second);
    }
    return result;
}

};