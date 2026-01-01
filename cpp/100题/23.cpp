#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> keyIndices;
        vector<int> result;
        
        // 首先找到所有key的位置
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == key) {
                keyIndices.push_back(i);
            }
        }
        
        // 对于每个位置i，检查是否存在key的位置j使得|i-j| <= k
        for (int i = 0; i < nums.size(); i++) {
            for (int j : keyIndices) {
                if (abs(i - j) <= k) {
                    result.push_back(i);
                    break; // 找到一个满足条件的j就可以停止
                }
            }
        }
        
        // 题目要求返回递增顺序的列表，而我们的遍历已经是递增的，所以不需要排序
        return result;
    }
};
