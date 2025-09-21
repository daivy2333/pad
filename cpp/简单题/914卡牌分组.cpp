#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        // 如果牌的数量小于2，直接返回false
        if (deck.size() < 2) {
            return false;
        }
        
        // 统计每个数字出现的次数
        unordered_map<int, int> count;
        for (int card : deck) {
            count[card]++;
        }
        
        // 计算所有出现次数的最大公约数
        int gcd = count.begin()->second;
        for (auto& p : count) {
            gcd = __gcd(gcd, p.second);
            // 如果在计算过程中gcd变成1，可以直接返回false
            if (gcd == 1) {
                return false;
            }
        }
        
        return gcd >= 2;
    }
};
/*
这是我第一次见到公约数这个函数gcd
*/