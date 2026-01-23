#include <vector>
using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        if (arr.size() < 3) return false;
        
        int i = 0;
        // 上升阶段
        while (i < arr.size() - 1 && arr[i] < arr[i + 1]) {
            i++;
        }
        
        // 检查是否到达山顶或山脚
        if (i == 0 || i == arr.size() - 1) {
            return false;
        }
        
        // 下降阶段
        while (i < arr.size() - 1 && arr[i] > arr[i + 1]) {
            i++;
        }
        
        // 如果遍历完整个数组，说明是有效的山脉数组
        return i == arr.size() - 1;
    }
};
